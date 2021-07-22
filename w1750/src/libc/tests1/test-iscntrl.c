/*
 * Test for ANSI Standard C: 7.3.1.3
 * 
 * #include <ctype.h>
 * int iscntrl (int c);
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


static char *_test_iscntrl_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(iscntrl ('\000'))) {
    failed ("Case 1: iscntrl ('\\000')");
  }
  
  /* Case 2 */
  if (!(iscntrl ('\001'))) {
    failed ("Case 2: iscntrl ('\\001')");
  }
  
  /* Case 3 */
  if (!(iscntrl ('\002'))) {
    failed ("Case 3: iscntrl ('\\002')");
  }
  
  /* Case 4 */
  if (!(iscntrl ('\003'))) {
    failed ("Case 4: iscntrl ('\\003')");
  }
  
  /* Case 5 */
  if (!(iscntrl ('\004'))) {
    failed ("Case 5: iscntrl ('\\004')");
  }
  
  /* Case 6 */
  if (!(iscntrl ('\005'))) {
    failed ("Case 6: iscntrl ('\\005')");
  }
  
  /* Case 7 */
  if (!(iscntrl ('\006'))) {
    failed ("Case 7: iscntrl ('\\006')");
  }
  
  /* Case 8 */
  if (!(iscntrl ('\007'))) {
    failed ("Case 8: iscntrl ('\\007')");
  }
  
  /* Case 9 */
  if (!(iscntrl ('\010'))) {
    failed ("Case 9: iscntrl ('\\010')");
  }
  
  /* Case 10 */
  if (!(iscntrl ('\011'))) {
    failed ("Case 10: iscntrl ('\\011')");
  }
  
  /* Case 11 */
  if (!(iscntrl ('\012'))) {
    failed ("Case 11: iscntrl ('\\012')");
  }
  
  /* Case 12 */
  if (!(iscntrl ('\013'))) {
    failed ("Case 12: iscntrl ('\\013')");
  }
  
  /* Case 13 */
  if (!(iscntrl ('\014'))) {
    failed ("Case 13: iscntrl ('\\014')");
  }
  
  /* Case 14 */
  if (!(iscntrl ('\015'))) {
    failed ("Case 14: iscntrl ('\\015')");
  }
  
  /* Case 15 */
  if (!(iscntrl ('\016'))) {
    failed ("Case 15: iscntrl ('\\016')");
  }
  
  /* Case 16 */
  if (!(iscntrl ('\017'))) {
    failed ("Case 16: iscntrl ('\\017')");
  }
  
  /* Case 17 */
  if (!(iscntrl ('\020'))) {
    failed ("Case 17: iscntrl ('\\020')");
  }
  
  /* Case 18 */
  if (!(iscntrl ('\021'))) {
    failed ("Case 18: iscntrl ('\\021')");
  }
  
  /* Case 19 */
  if (!(iscntrl ('\022'))) {
    failed ("Case 19: iscntrl ('\\022')");
  }
  
  /* Case 20 */
  if (!(iscntrl ('\023'))) {
    failed ("Case 20: iscntrl ('\\023')");
  }
  
  /* Case 21 */
  if (!(iscntrl ('\024'))) {
    failed ("Case 21: iscntrl ('\\024')");
  }
  
  /* Case 22 */
  if (!(iscntrl ('\025'))) {
    failed ("Case 22: iscntrl ('\\025')");
  }
  
  /* Case 23 */
  if (!(iscntrl ('\026'))) {
    failed ("Case 23: iscntrl ('\\026')");
  }
  
  /* Case 24 */
  if (!(iscntrl ('\027'))) {
    failed ("Case 24: iscntrl ('\\027')");
  }
  
  /* Case 25 */
  if (!(iscntrl ('\030'))) {
    failed ("Case 25: iscntrl ('\\030')");
  }
  
  /* Case 26 */
  if (!(iscntrl ('\031'))) {
    failed ("Case 26: iscntrl ('\\031')");
  }
  
  /* Case 27 */
  if (!(iscntrl ('\032'))) {
    failed ("Case 27: iscntrl ('\\032')");
  }
  
  /* Case 28 */
  if (!(iscntrl ('\033'))) {
    failed ("Case 28: iscntrl ('\\033')");
  }
  
  /* Case 29 */
  if (!(iscntrl ('\034'))) {
    failed ("Case 29: iscntrl ('\\034')");
  }
  
  /* Case 30 */
  if (!(iscntrl ('\035'))) {
    failed ("Case 30: iscntrl ('\\035')");
  }
  
  /* Case 31 */
  if (!(iscntrl ('\036'))) {
    failed ("Case 31: iscntrl ('\\036')");
  }
  
  /* Case 32 */
  if (!(iscntrl ('\037'))) {
    failed ("Case 32: iscntrl ('\\037')");
  }
  
  /* Case 33 */
  if (!(!iscntrl (' '))) {
    failed ("Case 33: !iscntrl (' ')");
  }
  
  /* Case 34 */
  if (!(!iscntrl ('!'))) {
    failed ("Case 34: !iscntrl ('!')");
  }
  
  /* Case 35 */
  if (!(!iscntrl ('\"'))) {
    failed ("Case 35: !iscntrl ('\\\"')");
  }
  
  /* Case 36 */
  if (!(!iscntrl ('#'))) {
    failed ("Case 36: !iscntrl ('#')");
  }
  
  /* Case 37 */
  if (!(!iscntrl ('$'))) {
    failed ("Case 37: !iscntrl ('$')");
  }
  
  /* Case 38 */
  if (!(!iscntrl ('%'))) {
    failed ("Case 38: !iscntrl ('%')");
  }
  
  /* Case 39 */
  if (!(!iscntrl ('&'))) {
    failed ("Case 39: !iscntrl ('&')");
  }
  
  /* Case 40 */
  if (!(!iscntrl ('\''))) {
    failed ("Case 40: !iscntrl ('\\'')");
  }
  
  /* Case 41 */
  if (!(!iscntrl ('('))) {
    failed ("Case 41: !iscntrl ('(')");
  }
  
  /* Case 42 */
  if (!(!iscntrl (')'))) {
    failed ("Case 42: !iscntrl (')')");
  }
  
  /* Case 43 */
  if (!(!iscntrl ('*'))) {
    failed ("Case 43: !iscntrl ('*')");
  }
  
  /* Case 44 */
  if (!(!iscntrl ('+'))) {
    failed ("Case 44: !iscntrl ('+')");
  }
  
  /* Case 45 */
  if (!(!iscntrl (','))) {
    failed ("Case 45: !iscntrl (',')");
  }
  
  /* Case 46 */
  if (!(!iscntrl ('-'))) {
    failed ("Case 46: !iscntrl ('-')");
  }
  
  /* Case 47 */
  if (!(!iscntrl ('.'))) {
    failed ("Case 47: !iscntrl ('.')");
  }
  
  /* Case 48 */
  if (!(!iscntrl ('/'))) {
    failed ("Case 48: !iscntrl ('/')");
  }
  
  /* Case 49 */
  if (!(!iscntrl ('0'))) {
    failed ("Case 49: !iscntrl ('0')");
  }
  
  /* Case 50 */
  if (!(!iscntrl ('1'))) {
    failed ("Case 50: !iscntrl ('1')");
  }
  
  /* Case 51 */
  if (!(!iscntrl ('2'))) {
    failed ("Case 51: !iscntrl ('2')");
  }
  
  /* Case 52 */
  if (!(!iscntrl ('3'))) {
    failed ("Case 52: !iscntrl ('3')");
  }
  
  /* Case 53 */
  if (!(!iscntrl ('4'))) {
    failed ("Case 53: !iscntrl ('4')");
  }
  
  /* Case 54 */
  if (!(!iscntrl ('5'))) {
    failed ("Case 54: !iscntrl ('5')");
  }
  
  /* Case 55 */
  if (!(!iscntrl ('6'))) {
    failed ("Case 55: !iscntrl ('6')");
  }
  
  /* Case 56 */
  if (!(!iscntrl ('7'))) {
    failed ("Case 56: !iscntrl ('7')");
  }
  
  /* Case 57 */
  if (!(!iscntrl ('8'))) {
    failed ("Case 57: !iscntrl ('8')");
  }
  
  /* Case 58 */
  if (!(!iscntrl ('9'))) {
    failed ("Case 58: !iscntrl ('9')");
  }
  
  /* Case 59 */
  if (!(!iscntrl (':'))) {
    failed ("Case 59: !iscntrl (':')");
  }
  
  /* Case 60 */
  if (!(!iscntrl (';'))) {
    failed ("Case 60: !iscntrl (';')");
  }
  
  /* Case 61 */
  if (!(!iscntrl ('<'))) {
    failed ("Case 61: !iscntrl ('<')");
  }
  
  /* Case 62 */
  if (!(!iscntrl ('='))) {
    failed ("Case 62: !iscntrl ('=')");
  }
  
  /* Case 63 */
  if (!(!iscntrl ('>'))) {
    failed ("Case 63: !iscntrl ('>')");
  }
  
  /* Case 64 */
  if (!(!iscntrl ('?'))) {
    failed ("Case 64: !iscntrl ('?')");
  }
  
  /* Case 65 */
  if (!(!iscntrl ('@'))) {
    failed ("Case 65: !iscntrl ('@')");
  }
  
  /* Case 66 */
  if (!(!iscntrl ('A'))) {
    failed ("Case 66: !iscntrl ('A')");
  }
  
  /* Case 67 */
  if (!(!iscntrl ('B'))) {
    failed ("Case 67: !iscntrl ('B')");
  }
  
  /* Case 68 */
  if (!(!iscntrl ('C'))) {
    failed ("Case 68: !iscntrl ('C')");
  }
  
  /* Case 69 */
  if (!(!iscntrl ('D'))) {
    failed ("Case 69: !iscntrl ('D')");
  }
  
  /* Case 70 */
  if (!(!iscntrl ('E'))) {
    failed ("Case 70: !iscntrl ('E')");
  }
  
  /* Case 71 */
  if (!(!iscntrl ('F'))) {
    failed ("Case 71: !iscntrl ('F')");
  }
  
  /* Case 72 */
  if (!(!iscntrl ('G'))) {
    failed ("Case 72: !iscntrl ('G')");
  }
  
  /* Case 73 */
  if (!(!iscntrl ('H'))) {
    failed ("Case 73: !iscntrl ('H')");
  }
  
  /* Case 74 */
  if (!(!iscntrl ('I'))) {
    failed ("Case 74: !iscntrl ('I')");
  }
  
  /* Case 75 */
  if (!(!iscntrl ('J'))) {
    failed ("Case 75: !iscntrl ('J')");
  }
  
  /* Case 76 */
  if (!(!iscntrl ('K'))) {
    failed ("Case 76: !iscntrl ('K')");
  }
  
  /* Case 77 */
  if (!(!iscntrl ('L'))) {
    failed ("Case 77: !iscntrl ('L')");
  }
  
  /* Case 78 */
  if (!(!iscntrl ('M'))) {
    failed ("Case 78: !iscntrl ('M')");
  }
  
  /* Case 79 */
  if (!(!iscntrl ('N'))) {
    failed ("Case 79: !iscntrl ('N')");
  }
  
  /* Case 80 */
  if (!(!iscntrl ('O'))) {
    failed ("Case 80: !iscntrl ('O')");
  }
  
  /* Case 81 */
  if (!(!iscntrl ('P'))) {
    failed ("Case 81: !iscntrl ('P')");
  }
  
  /* Case 82 */
  if (!(!iscntrl ('Q'))) {
    failed ("Case 82: !iscntrl ('Q')");
  }
  
  /* Case 83 */
  if (!(!iscntrl ('R'))) {
    failed ("Case 83: !iscntrl ('R')");
  }
  
  /* Case 84 */
  if (!(!iscntrl ('S'))) {
    failed ("Case 84: !iscntrl ('S')");
  }
  
  /* Case 85 */
  if (!(!iscntrl ('T'))) {
    failed ("Case 85: !iscntrl ('T')");
  }
  
  /* Case 86 */
  if (!(!iscntrl ('U'))) {
    failed ("Case 86: !iscntrl ('U')");
  }
  
  /* Case 87 */
  if (!(!iscntrl ('V'))) {
    failed ("Case 87: !iscntrl ('V')");
  }
  
  /* Case 88 */
  if (!(!iscntrl ('W'))) {
    failed ("Case 88: !iscntrl ('W')");
  }
  
  /* Case 89 */
  if (!(!iscntrl ('X'))) {
    failed ("Case 89: !iscntrl ('X')");
  }
  
  /* Case 90 */
  if (!(!iscntrl ('Y'))) {
    failed ("Case 90: !iscntrl ('Y')");
  }
  
  /* Case 91 */
  if (!(!iscntrl ('Z'))) {
    failed ("Case 91: !iscntrl ('Z')");
  }
  
  /* Case 92 */
  if (!(!iscntrl ('['))) {
    failed ("Case 92: !iscntrl ('[')");
  }
  
  /* Case 93 */
  if (!(!iscntrl ('\\'))) {
    failed ("Case 93: !iscntrl ('\\\\')");
  }
  
  /* Case 94 */
  if (!(!iscntrl (']'))) {
    failed ("Case 94: !iscntrl (']')");
  }
  
  /* Case 95 */
  if (!(!iscntrl ('^'))) {
    failed ("Case 95: !iscntrl ('^')");
  }
  
  /* Case 96 */
  if (!(!iscntrl ('_'))) {
    failed ("Case 96: !iscntrl ('_')");
  }
  
  /* Case 97 */
  if (!(!iscntrl ('`'))) {
    failed ("Case 97: !iscntrl ('`')");
  }
  
  /* Case 98 */
  if (!(!iscntrl ('a'))) {
    failed ("Case 98: !iscntrl ('a')");
  }
  
  /* Case 99 */
  if (!(!iscntrl ('b'))) {
    failed ("Case 99: !iscntrl ('b')");
  }
  
  /* Case 100 */
  if (!(!iscntrl ('c'))) {
    failed ("Case 100: !iscntrl ('c')");
  }
  
  /* Case 101 */
  if (!(!iscntrl ('d'))) {
    failed ("Case 101: !iscntrl ('d')");
  }
  
  /* Case 102 */
  if (!(!iscntrl ('e'))) {
    failed ("Case 102: !iscntrl ('e')");
  }
  
  /* Case 103 */
  if (!(!iscntrl ('f'))) {
    failed ("Case 103: !iscntrl ('f')");
  }
  
  /* Case 104 */
  if (!(!iscntrl ('g'))) {
    failed ("Case 104: !iscntrl ('g')");
  }
  
  /* Case 105 */
  if (!(!iscntrl ('h'))) {
    failed ("Case 105: !iscntrl ('h')");
  }
  
  /* Case 106 */
  if (!(!iscntrl ('i'))) {
    failed ("Case 106: !iscntrl ('i')");
  }
  
  /* Case 107 */
  if (!(!iscntrl ('j'))) {
    failed ("Case 107: !iscntrl ('j')");
  }
  
  /* Case 108 */
  if (!(!iscntrl ('k'))) {
    failed ("Case 108: !iscntrl ('k')");
  }
  
  /* Case 109 */
  if (!(!iscntrl ('l'))) {
    failed ("Case 109: !iscntrl ('l')");
  }
  
  /* Case 110 */
  if (!(!iscntrl ('m'))) {
    failed ("Case 110: !iscntrl ('m')");
  }
  
  /* Case 111 */
  if (!(!iscntrl ('n'))) {
    failed ("Case 111: !iscntrl ('n')");
  }
  
  /* Case 112 */
  if (!(!iscntrl ('o'))) {
    failed ("Case 112: !iscntrl ('o')");
  }
  
  /* Case 113 */
  if (!(!iscntrl ('p'))) {
    failed ("Case 113: !iscntrl ('p')");
  }
  
  /* Case 114 */
  if (!(!iscntrl ('q'))) {
    failed ("Case 114: !iscntrl ('q')");
  }
  
  /* Case 115 */
  if (!(!iscntrl ('r'))) {
    failed ("Case 115: !iscntrl ('r')");
  }
  
  /* Case 116 */
  if (!(!iscntrl ('s'))) {
    failed ("Case 116: !iscntrl ('s')");
  }
  
  /* Case 117 */
  if (!(!iscntrl ('t'))) {
    failed ("Case 117: !iscntrl ('t')");
  }
  
  /* Case 118 */
  if (!(!iscntrl ('u'))) {
    failed ("Case 118: !iscntrl ('u')");
  }
  
  /* Case 119 */
  if (!(!iscntrl ('v'))) {
    failed ("Case 119: !iscntrl ('v')");
  }
  
  /* Case 120 */
  if (!(!iscntrl ('w'))) {
    failed ("Case 120: !iscntrl ('w')");
  }
  
  /* Case 121 */
  if (!(!iscntrl ('x'))) {
    failed ("Case 121: !iscntrl ('x')");
  }
  
  /* Case 122 */
  if (!(!iscntrl ('y'))) {
    failed ("Case 122: !iscntrl ('y')");
  }
  
  /* Case 123 */
  if (!(!iscntrl ('z'))) {
    failed ("Case 123: !iscntrl ('z')");
  }
  
  /* Case 124 */
  if (!(!iscntrl ('{'))) {
    failed ("Case 124: !iscntrl ('{')");
  }
  
  /* Case 125 */
  if (!(!iscntrl ('|'))) {
    failed ("Case 125: !iscntrl ('|')");
  }
  
  /* Case 126 */
  if (!(!iscntrl ('}'))) {
    failed ("Case 126: !iscntrl ('}')");
  }
  
  /* Case 127 */
  if (!(!iscntrl ('~'))) {
    failed ("Case 127: !iscntrl ('~')");
  }
  
  /* Case 128 */
  if (!(iscntrl ('\177'))) {
    failed ("Case 128: iscntrl ('\\177')");
  }
  
}


void main ()
{
  test ("test-iscntrl", "Test for ANSI Standard C: 7.3.1.3");

  do_test ();

  result ();
}

