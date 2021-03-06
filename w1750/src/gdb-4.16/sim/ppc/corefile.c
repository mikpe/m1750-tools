/*  This file is part of the program psim.

    Copyright (C) 1994-1996, Andrew Cagney <cagney@highland.com.au>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
 
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
    */


#ifndef _CORE_C_
#define _CORE_C_

#include "basics.h"
#include "device_table.h"
#include "corefile.h"


typedef struct _core_mapping core_mapping;
struct _core_mapping {
  /* ram map */
  int free_buffer;
  void *buffer;
  /* device map */
  device *device;
  /* common */
  int space;
  unsigned_word base;
  unsigned_word bound;
  unsigned nr_bytes;
  core_mapping *next;
};

struct _core_map {
  core_mapping *first;
  core_mapping *default_map;
};

typedef enum {
  core_read_map,
  core_write_map,
  core_execute_map,
  nr_core_map_types,
} core_map_types;

struct _core {
  core_map map[nr_core_map_types];
};


INLINE_CORE\
(core *)
core_create(device *root)
{
  root = device_tree_find_device(root, "/");
  ASSERT(strcmp(device_name(root), "core") == 0);
  return device_data(root);
}


STATIC_INLINE_CORE\
(void)
core_init(core *memory)
{
  core_map_types access_type;
  for (access_type = 0;
       access_type < nr_core_map_types;
       access_type++) {
    core_map *map = memory->map + access_type;
    /* blow away old mappings */
    core_mapping *curr = map->first;
    while (curr != NULL) {
      core_mapping *tbd = curr;
      curr = curr->next;
      if (tbd->free_buffer) {
	ASSERT(tbd->buffer != NULL);
	zfree(tbd->buffer);
      }
      zfree(tbd);
    }
    map->first = NULL;
    /* blow away the default */
    if (map->default_map != NULL) {
      ASSERT(map->default_map->buffer == NULL);
      zfree(map->default_map);
    }
    map->default_map = NULL;
  }
}



/* the core has three sub mappings that the more efficient
   read/write fixed quantity functions use */

INLINE_CORE\
(core_map *)
core_readable(core *memory)
{
  return memory->map + core_read_map;
}

INLINE_CORE\
(core_map *)
core_writeable(core *memory)
{
  return memory->map + core_write_map;
}

INLINE_CORE\
(core_map *)
core_executable(core *memory)
{
  return memory->map + core_execute_map;
}



STATIC_INLINE_CORE\
(core_mapping *)
new_core_mapping(attach_type attach,
		 int space,
		 unsigned_word addr,
		 unsigned nr_bytes,
		 device *device,
		 void *buffer,
		 int free_buffer)
{
  core_mapping *new_mapping = ZALLOC(core_mapping);
  switch (attach) {
  case attach_default:
  case attach_callback:
    new_mapping->device = device;
    break;
  case attach_raw_memory:
    new_mapping->buffer = buffer;
    new_mapping->free_buffer = free_buffer;
    break;
  default:
    error("new_core_mapping() - internal error - unknown attach type %d\n",
	  attach);
  }
  /* common */
  new_mapping->space = space;
  new_mapping->base = addr;
  new_mapping->nr_bytes = nr_bytes;
  new_mapping->bound = addr + (nr_bytes - 1);
  return new_mapping;
}


STATIC_INLINE_CORE\
(void)
core_map_attach(core_map *access_map,
		attach_type attach,
		int space,
		unsigned_word addr,
		unsigned nr_bytes, /* host limited */
		device *device, /*callback/default*/
		void *buffer, /*raw_memory*/
		int free_buffer) /*raw_memory*/
{
  if (attach == attach_default) {
    if (access_map->default_map != NULL)
      error("core_map_attach() default mapping already in place\n");
    ASSERT(buffer == NULL);
    access_map->default_map = new_core_mapping(attach, 
					       space, addr, nr_bytes,
					       device, buffer, free_buffer);
  }
  else {
    /* find the insertion point for this additional mapping and insert */
    core_mapping *next_mapping;
    core_mapping **last_mapping;

    /* actually do occasionally get a zero size map */
    if (nr_bytes == 0)
      error("core_map_attach() size == 0\n");

    /* find the insertion point (between last/next) */
    next_mapping = access_map->first;
    last_mapping = &access_map->first;
    while(next_mapping != NULL && next_mapping->bound < addr) {
      /* assert: next_mapping->base > all bases before next_mapping */
      /* assert: next_mapping->bound >= all bounds before next_mapping */
      last_mapping = &next_mapping->next;
      next_mapping = next_mapping->next;
    }

    /* check insertion point correct */
    if (next_mapping != NULL && next_mapping->base < (addr + (nr_bytes - 1))) {
      error("core_map_attach() map overlap\n");
    }

    /* create/insert the new mapping */
    *last_mapping = new_core_mapping(attach,
				     space, addr, nr_bytes,
				     device, buffer, free_buffer);
    (*last_mapping)->next = next_mapping;
  }
}


INLINE_CORE\
(void)
core_attach(core *memory,
	    attach_type attach,
	    int space,
	    access_type access,
	    unsigned_word addr,
	    unsigned nr_bytes, /* host limited */
	    device *device) /*callback/default*/
{
  core_map_types access_map;
  int free_buffer = 0;
  void *buffer = NULL;
  ASSERT(attach == attach_default || nr_bytes > 0);
  if (attach == attach_raw_memory)
    buffer = zalloc(nr_bytes);
  for (access_map = 0; 
       access_map < nr_core_map_types;
       access_map++) {
    switch (access_map) {
    case core_read_map:
      if (access & access_read)
	core_map_attach(memory->map + access_map,
			attach,
			space, addr, nr_bytes,
			device, buffer, !free_buffer);
      free_buffer ++;
      break;
    case core_write_map:
      if (access & access_write)
	core_map_attach(memory->map + access_map,
			attach,
			space, addr, nr_bytes,
			device, buffer, !free_buffer);
      free_buffer ++;
      break;
    case core_execute_map:
      if (access & access_exec)
	core_map_attach(memory->map + access_map,
			attach,
			space, addr, nr_bytes,
			device, buffer, !free_buffer);
      free_buffer ++;
      break;
    default:
      error("core_attach() internal error\n");
      break;
    }
  }
  ASSERT(free_buffer > 0); /* must attach to at least one thing */
}


STATIC_INLINE_CORE\
(core_mapping *)
core_map_find_mapping(core_map *map,
		      unsigned_word addr,
		      unsigned nr_bytes,
		      cpu *processor,
		      unsigned_word cia,
		      int abort) /*either 0 or 1 - helps inline */
{
  core_mapping *mapping = map->first;
  ASSERT((addr & (nr_bytes - 1)) == 0); /* must be aligned */
  ASSERT((addr + (nr_bytes - 1)) >= addr); /* must not wrap */
  while (mapping != NULL) {
    if (addr >= mapping->base
	&& (addr + (nr_bytes - 1)) <= mapping->bound)
      return mapping;
    mapping = mapping->next;
  }
  if (map->default_map != NULL)
    return map->default_map;
  if (abort)
    error("core_find_mapping() - access to unmaped address, attach a default map to handle this - addr=0x%x nr_bytes=0x%x processor=0x%x cia=0x%x\n",
	  addr, nr_bytes, processor, cia);
  return NULL;
}


STATIC_INLINE_CORE\
(void *)
core_translate(core_mapping *mapping,
		     unsigned_word addr)
{
  return (void *)(((char *)mapping->buffer) + addr - mapping->base);
}


INLINE_CORE\
(unsigned)
core_map_read_buffer(core_map *map,
		     void *buffer,
		     unsigned_word addr,
		     unsigned len)
{
  unsigned count;
  unsigned_1 byte;
  for (count = 0; count < len; count++) {
    unsigned_word raddr = addr + count;
    core_mapping *mapping =
      core_map_find_mapping(map,
			    raddr, 1,
			    NULL, /*processor*/
			    0, /*cia*/
			    0); /*dont-abort*/
    if (mapping == NULL)
      break;
    if (mapping->device != NULL) {
      if (device_io_read_buffer(mapping->device,
				&byte,
				mapping->space,
				raddr,
				1, /* nr_bytes */
				0, /*processor*/
				0 /*cpu*/) != 1)
	break;
    }
    else
      byte = *(unsigned_1*)core_translate(mapping,
						raddr);
    ((unsigned_1*)buffer)[count] = T2H_1(byte);
  }
  return count;
}


INLINE_CORE\
(unsigned)
core_map_write_buffer(core_map *map,
		      const void *buffer,
		      unsigned_word addr,
		      unsigned len)
{
  unsigned count;
  unsigned_1 byte;
  for (count = 0; count < len; count++) {
    unsigned_word raddr = addr + count;
    core_mapping *mapping = core_map_find_mapping(map,
						  raddr, 1,
						  NULL, /*processor*/
						  0, /*cia*/
						  0); /*dont-abort*/
    if (mapping == NULL)
      break;
    byte = H2T_1(((unsigned_1*)buffer)[count]);
    if (mapping->device != NULL) {
      if (device_io_write_buffer(mapping->device,
				 &byte,
				 mapping->space,
				 raddr,
				 1, /*nr_bytes*/
				 0, /*processor*/
				 0 /*cpu*/) != 1)
	break;
    }
    else
      *(unsigned_1*)core_translate(mapping, raddr) = byte;
  }
  return count;
}


/* define the read/write 1/2/4/8/word functions */

#define N 1
#include "corefile-n.h"
#undef N

#define N 2
#include "corefile-n.h"
#undef N

#define N 4
#include "corefile-n.h"
#undef N

#define N 8
#include "corefile-n.h"
#undef N

#define N word
#include "corefile-n.h"
#undef N


/* Top level core(root) device: core@garbage

   The core device captures incomming dma requests and changes them to
   outgoing io requests. */

STATIC_INLINE_CORE\
(void)
core_init_address_callback(device *me,
			   psim *system)
{
  core *memory = (core*)device_data(me);
  core_init(memory);
}


STATIC_INLINE_CORE\
(void)
core_attach_address_callback(device *me,
			     const char *name,
			     attach_type attach,
			     int space,
			     unsigned_word addr,
			     unsigned nr_bytes,
			     access_type access,
			     device *who) /*callback/default*/
{
  core *memory = (core*)device_data(me);
  if (space != 0)
    error("core_attach_address_callback() invalid address space\n");
  core_attach(memory,
	      attach,
	      space,
	      access,
	      addr,
	      nr_bytes,
	      who);
}


STATIC_INLINE_CORE\
(unsigned)
core_dma_read_buffer_callback(device *me,
			      void *dest,
			      int space,
			      unsigned_word addr,
			      unsigned nr_bytes)
{
  core *memory = (core*)device_data(me);
  return core_map_read_buffer(core_readable(memory),
			      dest,
			      addr,
			      nr_bytes);
}


STATIC_INLINE_CORE\
(unsigned)
core_dma_write_buffer_callback(device *me,
			       const void *source,
			       int space,
			       unsigned_word addr,
			       unsigned nr_bytes,
			       int violate_read_only_section)
{
  core *memory = (core*)device_data(me);
  core_map *map = (violate_read_only_section
		   ? core_readable(memory)
		   : core_writeable(memory));
  return core_map_write_buffer(map,
			       source,
			       addr,
			       nr_bytes);
}

static device_callbacks const core_callbacks = {
  core_init_address_callback,
  ignore_device_init,
  core_attach_address_callback,
  unimp_device_detach_address,
  unimp_device_io_read_buffer,
  unimp_device_io_write_buffer,
  core_dma_read_buffer_callback,
  core_dma_write_buffer_callback,
  unimp_device_interrupt_event,
  unimp_device_child_interrupt_event,
  generic_device_unit_decode,
  generic_device_unit_encode,
  unimp_device_instance_create,
  unimp_device_instance_delete,
  unimp_device_instance_read,
  unimp_device_instance_write,
  unimp_device_instance_seek,
  unimp_device_ioctl,
};


INLINE_CORE\
(device *)
core_device_create(void)
{
  core *memory = ZALLOC(core);
  device_unit unit_address = { 0 };
  return device_create_from("core", &unit_address,
			    memory, &core_callbacks, NULL);
}


#endif /* _CORE_C_ */
