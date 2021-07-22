# GCC-1750 libpthread Makefile
#
# $Log: Makefile,v $
# Revision 1.2  1997/08/10 08:54:24  nettleto
# Added expanded memory version
#
# Revision 1.1  1997/07/18 16:35:15  nettleto
# Initial revision
#
#

all: libpthread.a libpthreadx.a


LIBPTHREAD_OBJS = \
    libpthread.a(clock_gettime.o)  \
    libpthread.a(intwait.o)  \
    libpthread.a(nanosleep.o)  \
    libpthread.a(pthread_attr_destroy.o)  \
    libpthread.a(pthread_attr_getdetachstate.o)  \
    libpthread.a(pthread_attr_getinheritsched.o)  \
    libpthread.a(pthread_attr_getschedparam.o)  \
    libpthread.a(pthread_attr_getschedpolicy.o)  \
    libpthread.a(pthread_attr_getstacksize.o)  \
    libpthread.a(pthread_attr_init.o)  \
    libpthread.a(pthread_attr_setdetachstate.o)  \
    libpthread.a(pthread_attr_setinheritsched.o)  \
    libpthread.a(pthread_attr_setschedparam.o)  \
    libpthread.a(pthread_attr_setschedpolicy.o)  \
    libpthread.a(pthread_attr_setstacksize.o)  \
    libpthread.a(pthread_cancel_timed_sigwait.o)  \
    libpthread.a(pthread_cleanup_push_pop.o)  \
    libpthread.a(pthread_clear_kernel_flag.o)  \
    libpthread.a(pthread_cond_broadcast.o)  \
    libpthread.a(pthread_cond_destroy.o)  \
    libpthread.a(pthread_cond_init.o)  \
    libpthread.a(pthread_cond_signal.o)  \
    libpthread.a(pthread_cond_timedwait.o)  \
    libpthread.a(pthread_cond_wait.o)  \
    libpthread.a(pthread_create.o)  \
    libpthread.a(pthread_detach.o)  \
    libpthread.a(pthread_equal.o)  \
    libpthread.a(pthread_exit.o)  \
    libpthread.a(pthread_getschedparam.o)  \
    libpthread.a(pthread_init.o)  \
    libpthread.a(pthread_join.o)  \
    libpthread.a(pthread_mutex_destroy.o)  \
    libpthread.a(pthread_mutex_init.o)  \
    libpthread.a(pthread_mutex_lock.o)  \
    libpthread.a(pthread_mutex_trylock.o)  \
    libpthread.a(pthread_mutex_unlock.o)  \
    libpthread.a(pthread_once.o)  \
    libpthread.a(pthread_q_deq.o)  \
    libpthread.a(pthread_q_deq_head.o)  \
    libpthread.a(pthread_q_enq.o)  \
    libpthread.a(pthread_q_sleep.o)  \
    libpthread.a(pthread_q_sleep_thread.o)  \
    libpthread.a(pthread_q_wakeup.o)  \
    libpthread.a(pthread_q_wakeup_all.o)  \
    libpthread.a(pthread_q_wakeup_thread.o)  \
    libpthread.a(pthread_self.o)  \
    libpthread.a(pthread_setschedparam.o)  \
    libpthread.a(pthread_specific_data.o)  \
    libpthread.a(pthread_switch_handler.o)  \
    libpthread.a(pthread_timed_sigwait.o)  \
    libpthread.a(sched_get_priority_max.o)  \
    libpthread.a(sched_get_priority_min.o)  \
    libpthread.a(sched_yield.o)  \
    libpthread.a(sleep.o)

LIBPTHREAD_XOBJS = \
    libpthreadx.a(clock_gettime.o)  \
    libpthreadx.a(intwait.o)  \
    libpthreadx.a(nanosleep.o)  \
    libpthreadx.a(pthread_attr_destroy.o)  \
    libpthreadx.a(pthread_attr_getdetachstate.o)  \
    libpthreadx.a(pthread_attr_getinheritsched.o)  \
    libpthreadx.a(pthread_attr_getschedparam.o)  \
    libpthreadx.a(pthread_attr_getschedpolicy.o)  \
    libpthreadx.a(pthread_attr_getstacksize.o)  \
    libpthreadx.a(pthread_attr_init.o)  \
    libpthreadx.a(pthread_attr_setdetachstate.o)  \
    libpthreadx.a(pthread_attr_setinheritsched.o)  \
    libpthreadx.a(pthread_attr_setschedparam.o)  \
    libpthreadx.a(pthread_attr_setschedpolicy.o)  \
    libpthreadx.a(pthread_attr_setstacksize.o)  \
    libpthreadx.a(pthread_cancel_timed_sigwait.o)  \
    libpthreadx.a(pthread_cleanup_push_pop.o)  \
    libpthreadx.a(pthread_clear_kernel_flag.o)  \
    libpthreadx.a(pthread_cond_broadcast.o)  \
    libpthreadx.a(pthread_cond_destroy.o)  \
    libpthreadx.a(pthread_cond_init.o)  \
    libpthreadx.a(pthread_cond_signal.o)  \
    libpthreadx.a(pthread_cond_timedwait.o)  \
    libpthreadx.a(pthread_cond_wait.o)  \
    libpthreadx.a(pthread_create.o)  \
    libpthreadx.a(pthread_detach.o)  \
    libpthreadx.a(pthread_equal.o)  \
    libpthreadx.a(pthread_exit.o)  \
    libpthreadx.a(pthread_getschedparam.o)  \
    libpthreadx.a(pthread_init.o)  \
    libpthreadx.a(pthread_join.o)  \
    libpthreadx.a(pthread_mutex_destroy.o)  \
    libpthreadx.a(pthread_mutex_init.o)  \
    libpthreadx.a(pthread_mutex_lock.o)  \
    libpthreadx.a(pthread_mutex_trylock.o)  \
    libpthreadx.a(pthread_mutex_unlock.o)  \
    libpthreadx.a(pthread_once.o)  \
    libpthreadx.a(pthread_q_deq.o)  \
    libpthreadx.a(pthread_q_deq_head.o)  \
    libpthreadx.a(pthread_q_enq.o)  \
    libpthreadx.a(pthread_q_sleep.o)  \
    libpthreadx.a(pthread_q_sleep_thread.o)  \
    libpthreadx.a(pthread_q_wakeup.o)  \
    libpthreadx.a(pthread_q_wakeup_all.o)  \
    libpthreadx.a(pthread_q_wakeup_thread.o)  \
    libpthreadx.a(pthread_self.o)  \
    libpthreadx.a(pthread_setschedparam.o)  \
    libpthreadx.a(pthread_specific_data.o)  \
    libpthreadx.a(pthread_switch_handler.o)  \
    libpthreadx.a(pthread_timed_sigwait.o)  \
    libpthreadx.a(sched_get_priority_max.o)  \
    libpthreadx.a(sched_get_priority_min.o)  \
    libpthreadx.a(sched_yield.o)  \
    libpthreadx.a(sleep.o)


libpthread.a: $(LIBPTHREAD_OBJS)
	@echo "$@ is now up-to-date"

libpthreadx.a: $(LIBPTHREAD_XOBJS)
	@echo "$@ is now up-to-date"

clean:
	rm -rf *.a *.o

