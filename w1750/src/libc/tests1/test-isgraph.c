/*
 * Test for ANSI Standard C: 7.3.1.5
 * 
 * #include <ctype.h>
 * int isgraph (int c);
 * 
 * Copyright (c) 1996, Chris Nettleton Software
 *
 * The authors hereby grant permission to use, copy, modify, distribute, 
 * and license this software and its documentation for any purpose, 
 * provided that existing copyright notices are retained in all copies 
 * and that this notice is included verbatim in any distributions. No 
 * written agreement, license, or royalty fee is required for any of the 
 * authorized uses. Modifications to this software may be copyrighted by 
 * their authors and need not follow the licensing terms described here, 
 * provided that the new terms are clearly indicated on the first page 
 * of each file where they apply. 
 *
 * $Log$
 */

#include <report.h>

#include <ctype.h>


static char *_test_isgraph_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(!isgraph ('\000'))) {
    failed ("Case 1: !isgraph ('\\000')");
  }
  
  /* Case 2 */
  if (!(!isgraph ('\001'))) {
    failed ("Case 2: !isgraph ('\\001')");
  }
  
  /* Case 3 */
  if (!(!isgraph ('\002'))) {
    failed ("Case 3: !isgraph ('\\002')");
  }
  
  /* Case 4 */
  if (!(!isgraph ('\003'))) {
    failed ("Case 4: !isgraph ('\\003')");
  }
  
  /* Case 5 */
  if (!(!isgraph ('\004'))) {
    failed ("Case 5: !isgraph ('\\004')");
  }
  
  /* Case 6 */
  if (!(!isgraph ('\005'))) {
    failed ("Case 6: !isgraph ('\\005')");
  }
  
  /* Case 7 */
  if (!(!isgraph ('\006'))) {
    failed ("Case 7: !isgraph ('\\006')");
  }
  
  /* Case 8 */
  if (!(!isgraph ('\007'))) {
    failed ("Case 8: !isgraph ('\\007')");
  }
  
  /* Case 9 */
  if (!(!isgraph ('\010'))) {
    failed ("Case 9: !isgraph ('\\010')");
  }
  
  /* Case 10 */
  if (!(!isgraph ('\011'))) {
    failed ("Case 10: !isgraph ('\\011')");
  }
  
  /* Case 11 */
  if (!(!isgraph ('\012'))) {
    failed ("Case 11: !isgraph ('\\012')");
  }
  
  /* Case 12 */
  if (!(!isgraph ('\013'))) {
    failed ("Case 12: !isgraph ('\\013')");
  }
  
  /* Case 13 */
  if (!(!isgraph ('\014'))) {
    failed ("Case 13: !isgraph ('\\014')");
  }
  
  /* Case 14 */
  if (!(!isgraph ('\015'))) {
    failed ("Case 14: !isgraph ('\\015')");
  }
  
  /* Case 15 */
  if (!(!isgraph ('\016'))) {
    failed ("Case 15: !isgraph ('\\016')");
  }
  
  /* Case 16 */
  if (!(!isgraph ('\017'))) {
    failed ("Case 16: !isgraph ('\\017')");
  }
  
  /* Case 17 */
  if (!(!isgraph ('\020'))) {
    failed ("Case 17: !isgraph ('\\020')");
  }
  
  /* Case 18 */
  if (!(!isgraph ('\021'))) {
    failed ("Case 18: !isgraph ('\\021')");
  }
  
  /* Case 19 */
  if (!(!isgraph ('\022'))) {
    failed ("Case 19: !isgraph ('\\022')");
  }
  
  /* Case 20 */
  if (!(!isgraph ('\023'))) {
    failed ("Case 20: !isgraph ('\\023')");
  }
  
  /* Case 21 */
  if (!(!isgraph ('\024'))) {
    failed ("Case 21: !isgraph ('\\024')");
  }
  
  /* Case 22 */
  if (!(!isgraph ('\025'))) {
    failed ("Case 22: !isgraph ('\\025')");
  }
  
  /* Case 23 */
  if (!(!isgraph ('\026'))) {
    failed ("Case 23: !isgraph ('\\026')");
  }
  
  /* Case 24 */
  if (!(!isgraph ('\027'))) {
    failed ("Case 24: !isgraph ('\\027')");
  }
  
  /* Case 25 */
  if (!(!isgraph ('\030'))) {
    failed ("Case 25: !isgraph ('\\030')");
  }
  
  /* Case 26 */
  if (!(!isgraph ('\031'))) {
    failed ("Case 26: !isgraph ('\\031')");
  }
  
  /* Case 27 */
  if (!(!isgraph ('\032'))) {
    failed ("Case 27: !isgraph ('\\032')");
  }
  
  /* Case 28 */
  if (!(!isgraph ('\033'))) {
    failed ("Case 28: !isgraph ('\\033')");
  }
  
  /* Case 29 */
  if (!(!isgraph ('\034'))) {
    failed ("Case 29: !isgraph ('\\034')");
  }
  
  /* Case 30 */
  if (!(!isgraph ('\035'))) {
    failed ("Case 30: !isgraph ('\\035')");
  }
  
  /* Case 31 */
  if (!(!isgraph ('\036'))) {
    failed ("Case 31: !isgraph ('\\036')");
  }
  
  /* Case 32 */
  if (!(!isgraph ('\037'))) {
    failed ("Case 32: !isgraph ('\\037')");
  }
  
  /* Case 33 */
  if (!(!isgraph (' '))) {
    failed ("Case 33: !isgraph (' ')");
  }
  
  /* Case 34 */
  if (!(isgraph ('!'))) {
    failed ("Case 34: isgraph ('!')");
  }
  
  /* Case 35 */
  if (!(isgraph ('\"'))) {
    failed ("Case 35: isgraph ('\\\"')");
  }
  
  /* Case 36 */
  if (!(isgraph ('#'))) {
    failed ("Case 36: isgraph ('#')");
  }
  
  /* Case 37 */
  if (!(isgraph ('$'))) {
    failed ("Case 37: isgraph ('$')");
  }
  
  /* Case 38 */
  if (!(isgraph ('%'))) {
    failed ("Case 38: isgraph ('%')");
  }
  
  /* Case 39 */
  if (!(isgraph ('&'))) {
    failed ("Case 39: isgraph ('&')");
  }
  
  /* Case 40 */
  if (!(isgraph ('\''))) {
    failed ("Case 40: isgraph ('\\'')");
  }
  
  /* Case 41 */
  if (!(isgraph ('('))) {
    failed ("Case 41: isgraph ('(')");
  }
  
  /* Case 42 */
  if (!(isgraph (')'))) {
    failed ("Case 42: isgraph (')')");
  }
  
  /* Case 43 */
  if (!(isgraph ('*'))) {
    failed ("Case 43: isgraph ('*')");
  }
  
  /* Case 44 */
  if (!(isgraph ('+'))) {
    failed ("Case 44: isgraph ('+')");
  }
  
  /* Case 45 */
  if (!(isgraph (','))) {
    failed ("Case 45: isgraph (',')");
  }
  
  /* Case 46 */
  if (!(isgraph ('-'))) {
    failed ("Case 46: isgraph ('-')");
  }
  
  /* Case 47 */
  if (!(isgraph ('.'))) {
    failed ("Case 47: isgraph ('.')");
  }
  
  /* Case 48 */
  if (!(isgraph ('/'))) {
    failed ("Case 48: isgraph ('/')");
  }
  
  /* Case 49 */
  if (!(isgraph ('0'))) {
    failed ("Case 49: isgraph ('0')");
  }
  
  /* Case 50 */
  if (!(isgraph ('1'))) {
    failed ("Case 50: isgraph ('1')");
  }
  
  /* Case 51 */
  if (!(isgraph ('2'))) {
    failed ("Case 51: isgraph ('2')");
  }
  
  /* Case 52 */
  if (!(isgraph ('3'))) {
    failed ("Case 52: isgraph ('3')");
  }
  
  /* Case 53 */
  if (!(isgraph ('4'))) {
    failed ("Case 53: isgraph ('4')");
  }
  
  /* Case 54 */
  if (!(isgraph ('5'))) {
    failed ("Case 54: isgraph ('5')");
  }
  
  /* Case 55 */
  if (!(isgraph ('6'))) {
    failed ("Case 55: isgraph ('6')");
  }
  
  /* Case 56 */
  if (!(isgraph ('7'))) {
    failed ("Case 56: isgraph ('7')");
  }
  
  /* Case 57 */
  if (!(isgraph ('8'))) {
    failed ("Case 57: isgraph ('8')");
  }
  
  /* Case 58 */
  if (!(isgraph ('9'))) {
    failed ("Case 58: isgraph ('9')");
  }
  
  /* Case 59 */
  if (!(isgraph (':'))) {
    failed ("Case 59: isgraph (':')");
  }
  
  /* Case 60 */
  if (!(isgraph (';'))) {
    failed ("Case 60: isgraph (';')");
  }
  
  /* Case 61 */
  if (!(isgraph ('<'))) {
    failed ("Case 61: isgraph ('<')");
  }
  
  /* Case 62 */
  if (!(isgraph ('='))) {
    failed ("Case 62: isgraph ('=')");
  }
  
  /* Case 63 */
  if (!(isgraph ('>'))) {
    failed ("Case 63: isgraph ('>')");
  }
  
  /* Case 64 */
  if (!(isgraph ('?'))) {
    failed ("Case 64: isgraph ('?')");
  }
  
  /* Case 65 */
  if (!(isgraph ('@'))) {
    failed ("Case 65: isgraph ('@')");
  }
  
  /* Case 66 */
  if (!(isgraph ('A'))) {
    failed ("Case 66: isgraph ('A')");
  }
  
  /* Case 67 */
  if (!(isgraph ('B'))) {
    failed ("Case 67: isgraph ('B')");
  }
  
  /* Case 68 */
  if (!(isgraph ('C'))) {
    failed ("Case 68: isgraph ('C')");
  }
  
  /* Case 69 */
  if (!(isgraph ('D'))) {
    failed ("Case 69: isgraph ('D')");
  }
  
  /* Case 70 */
  if (!(isgraph ('E'))) {
    failed ("Case 70: isgraph ('E')");
  }
  
  /* Case 71 */
  if (!(isgraph ('F'))) {
    failed ("Case 71: isgraph ('F')");
  }
  
  /* Case 72 */
  if (!(isgraph ('G'))) {
    failed ("Case 72: isgraph ('G')");
  }
  
  /* Case 73 */
  if (!(isgraph ('H'))) {
    failed ("Case 73: isgraph ('H')");
  }
  
  /* Case 74 */
  if (!(isgraph ('I'))) {
    failed ("Case 74: isgraph ('I')");
  }
  
  /* Case 75 */
  if (!(isgraph ('J'))) {
    failed ("Case 75: isgraph ('J')");
  }
  
  /* Case 76 */
  if (!(isgraph ('K'))) {
    failed ("Case 76: isgraph ('K')");
  }
  
  /* Case 77 */
  if (!(isgraph ('L'))) {
    failed ("Case 77: isgraph ('L')");
  }
  
  /* Case 78 */
  if (!(isgraph ('M'))) {
    failed ("Case 78: isgraph ('M')");
  }
  
  /* Case 79 */
  if (!(isgraph ('N'))) {
    failed ("Case 79: isgraph ('N')");
  }
  
  /* Case 80 */
  if (!(isgraph ('O'))) {
    failed ("Case 80: isgraph ('O')");
  }
  
  /* Case 81 */
  if (!(isgraph ('P'))) {
    failed ("Case 81: isgraph ('P')");
  }
  
  /* Case 82 */
  if (!(isgraph ('Q'))) {
    failed ("Case 82: isgraph ('Q')");
  }
  
  /* Case 83 */
  if (!(isgraph ('R'))) {
    failed ("Case 83: isgraph ('R')");
  }
  
  /* Case 84 */
  if (!(isgraph ('S'))) {
    failed ("Case 84: isgraph ('S')");
  }
  
  /* Case 85 */
  if (!(isgraph ('T'))) {
    failed ("Case 85: isgraph ('T')");
  }
  
  /* Case 86 */
  if (!(isgraph ('U'))) {
    failed ("Case 86: isgraph ('U')");
  }
  
  /* Case 87 */
  if (!(isgraph ('V'))) {
    failed ("Case 87: isgraph ('V')");
  }
  
  /* Case 88 */
  if (!(isgraph ('W'))) {
    failed ("Case 88: isgraph ('W')");
  }
  
  /* Case 89 */
  if (!(isgraph ('X'))) {
    failed ("Case 89: isgraph ('X')");
  }
  
  /* Case 90 */
  if (!(isgraph ('Y'))) {
    failed ("Case 90: isgraph ('Y')");
  }
  
  /* Case 91 */
  if (!(isgraph ('Z'))) {
    failed ("Case 91: isgraph ('Z')");
  }
  
  /* Case 92 */
  if (!(isgraph ('['))) {
    failed ("Case 92: isgraph ('[')");
  }
  
  /* Case 93 */
  if (!(isgraph ('\\'))) {
    failed ("Case 93: isgraph ('\\\\')");
  }
  
  /* Case 94 */
  if (!(isgraph (']'))) {
    failed ("Case 94: isgraph (']')");
  }
  
  /* Case 95 */
  if (!(isgraph ('^'))) {
    failed ("Case 95: isgraph ('^')");
  }
  
  /* Case 96 */
  if (!(isgraph ('_'))) {
    failed ("Case 96: isgraph ('_')");
  }
  
  /* Case 97 */
  if (!(isgraph ('`'))) {
    failed ("Case 97: isgraph ('`')");
  }
  
  /* Case 98 */
  if (!(isgraph ('a'))) {
    failed ("Case 98: isgraph ('a')");
  }
  
  /* Case 99 */
  if (!(isgraph ('b'))) {
    failed ("Case 99: isgraph ('b')");
  }
  
  /* Case 100 */
  if (!(isgraph ('c'))) {
    failed ("Case 100: isgraph ('c')");
  }
  
  /* Case 101 */
  if (!(isgraph ('d'))) {
    failed ("Case 101: isgraph ('d')");
  }
  
  /* Case 102 */
  if (!(isgraph ('e'))) {
    failed ("Case 102: isgraph ('e')");
  }
  
  /* Case 103 */
  if (!(isgraph ('f'))) {
    failed ("Case 103: isgraph ('f')");
  }
  
  /* Case 104 */
  if (!(isgraph ('g'))) {
    failed ("Case 104: isgraph ('g')");
  }
  
  /* Case 105 */
  if (!(isgraph ('h'))) {
    failed ("Case 105: isgraph ('h')");
  }
  
  /* Case 106 */
  if (!(isgraph ('i'))) {
    failed ("Case 106: isgraph ('i')");
  }
  
  /* Case 107 */
  if (!(isgraph ('j'))) {
    failed ("Case 107: isgraph ('j')");
  }
  
  /* Case 108 */
  if (!(isgraph ('k'))) {
    failed ("Case 108: isgraph ('k')");
  }
  
  /* Case 109 */
  if (!(isgraph ('l'))) {
    failed ("Case 109: isgraph ('l')");
  }
  
  /* Case 110 */
  if (!(isgraph ('m'))) {
    failed ("Case 110: isgraph ('m')");
  }
  
  /* Case 111 */
  if (!(isgraph ('n'))) {
    failed ("Case 111: isgraph ('n')");
  }
  
  /* Case 112 */
  if (!(isgraph ('o'))) {
    failed ("Case 112: isgraph ('o')");
  }
  
  /* Case 113 */
  if (!(isgraph ('p'))) {
    failed ("Case 113: isgraph ('p')");
  }
  
  /* Case 114 */
  if (!(isgraph ('q'))) {
    failed ("Case 114: isgraph ('q')");
  }
  
  /* Case 115 */
  if (!(isgraph ('r'))) {
    failed ("Case 115: isgraph ('r')");
  }
  
  /* Case 116 */
  if (!(isgraph ('s'))) {
    failed ("Case 116: isgraph ('s')");
  }
  
  /* Case 117 */
  if (!(isgraph ('t'))) {
    failed ("Case 117: isgraph ('t')");
  }
  
  /* Case 118 */
  if (!(isgraph ('u'))) {
    failed ("Case 118: isgraph ('u')");
  }
  
  /* Case 119 */
  if (!(isgraph ('v'))) {
    failed ("Case 119: isgraph ('v')");
  }
  
  /* Case 120 */
  if (!(isgraph ('w'))) {
    failed ("Case 120: isgraph ('w')");
  }
  
  /* Case 121 */
  if (!(isgraph ('x'))) {
    failed ("Case 121: isgraph ('x')");
  }
  
  /* Case 122 */
  if (!(isgraph ('y'))) {
    failed ("Case 122: isgraph ('y')");
  }
  
  /* Case 123 */
  if (!(isgraph ('z'))) {
    failed ("Case 123: isgraph ('z')");
  }
  
  /* Case 124 */
  if (!(isgraph ('{'))) {
    failed ("Case 124: isgraph ('{')");
  }
  
  /* Case 125 */
  if (!(isgraph ('|'))) {
    failed ("Case 125: isgraph ('|')");
  }
  
  /* Case 126 */
  if (!(isgraph ('}'))) {
    failed ("Case 126: isgraph ('}')");
  }
  
  /* Case 127 */
  if (!(isgraph ('~'))) {
    failed ("Case 127: isgraph ('~')");
  }
  
  /* Case 128 */
  if (!(!isgraph ('\177'))) {
    failed ("Case 128: !isgraph ('\\177')");
  }
  
}


void main ()
{
  test ("test-isgraph", "Test for ANSI Standard C: 7.3.1.5");

  do_test ();

  result ();
}

