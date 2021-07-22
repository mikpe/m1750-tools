/*
 * Test for ANSI Standard C: 7.3.1.8
 * 
 * #include <ctype.h>
 * int ispunct (int c);
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


static char *_test_ispunct_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(!ispunct ('\000'))) {
    failed ("Case 1: !ispunct ('\\000')");
  }
  
  /* Case 2 */
  if (!(!ispunct ('\001'))) {
    failed ("Case 2: !ispunct ('\\001')");
  }
  
  /* Case 3 */
  if (!(!ispunct ('\002'))) {
    failed ("Case 3: !ispunct ('\\002')");
  }
  
  /* Case 4 */
  if (!(!ispunct ('\003'))) {
    failed ("Case 4: !ispunct ('\\003')");
  }
  
  /* Case 5 */
  if (!(!ispunct ('\004'))) {
    failed ("Case 5: !ispunct ('\\004')");
  }
  
  /* Case 6 */
  if (!(!ispunct ('\005'))) {
    failed ("Case 6: !ispunct ('\\005')");
  }
  
  /* Case 7 */
  if (!(!ispunct ('\006'))) {
    failed ("Case 7: !ispunct ('\\006')");
  }
  
  /* Case 8 */
  if (!(!ispunct ('\007'))) {
    failed ("Case 8: !ispunct ('\\007')");
  }
  
  /* Case 9 */
  if (!(!ispunct ('\010'))) {
    failed ("Case 9: !ispunct ('\\010')");
  }
  
  /* Case 10 */
  if (!(!ispunct ('\011'))) {
    failed ("Case 10: !ispunct ('\\011')");
  }
  
  /* Case 11 */
  if (!(!ispunct ('\012'))) {
    failed ("Case 11: !ispunct ('\\012')");
  }
  
  /* Case 12 */
  if (!(!ispunct ('\013'))) {
    failed ("Case 12: !ispunct ('\\013')");
  }
  
  /* Case 13 */
  if (!(!ispunct ('\014'))) {
    failed ("Case 13: !ispunct ('\\014')");
  }
  
  /* Case 14 */
  if (!(!ispunct ('\015'))) {
    failed ("Case 14: !ispunct ('\\015')");
  }
  
  /* Case 15 */
  if (!(!ispunct ('\016'))) {
    failed ("Case 15: !ispunct ('\\016')");
  }
  
  /* Case 16 */
  if (!(!ispunct ('\017'))) {
    failed ("Case 16: !ispunct ('\\017')");
  }
  
  /* Case 17 */
  if (!(!ispunct ('\020'))) {
    failed ("Case 17: !ispunct ('\\020')");
  }
  
  /* Case 18 */
  if (!(!ispunct ('\021'))) {
    failed ("Case 18: !ispunct ('\\021')");
  }
  
  /* Case 19 */
  if (!(!ispunct ('\022'))) {
    failed ("Case 19: !ispunct ('\\022')");
  }
  
  /* Case 20 */
  if (!(!ispunct ('\023'))) {
    failed ("Case 20: !ispunct ('\\023')");
  }
  
  /* Case 21 */
  if (!(!ispunct ('\024'))) {
    failed ("Case 21: !ispunct ('\\024')");
  }
  
  /* Case 22 */
  if (!(!ispunct ('\025'))) {
    failed ("Case 22: !ispunct ('\\025')");
  }
  
  /* Case 23 */
  if (!(!ispunct ('\026'))) {
    failed ("Case 23: !ispunct ('\\026')");
  }
  
  /* Case 24 */
  if (!(!ispunct ('\027'))) {
    failed ("Case 24: !ispunct ('\\027')");
  }
  
  /* Case 25 */
  if (!(!ispunct ('\030'))) {
    failed ("Case 25: !ispunct ('\\030')");
  }
  
  /* Case 26 */
  if (!(!ispunct ('\031'))) {
    failed ("Case 26: !ispunct ('\\031')");
  }
  
  /* Case 27 */
  if (!(!ispunct ('\032'))) {
    failed ("Case 27: !ispunct ('\\032')");
  }
  
  /* Case 28 */
  if (!(!ispunct ('\033'))) {
    failed ("Case 28: !ispunct ('\\033')");
  }
  
  /* Case 29 */
  if (!(!ispunct ('\034'))) {
    failed ("Case 29: !ispunct ('\\034')");
  }
  
  /* Case 30 */
  if (!(!ispunct ('\035'))) {
    failed ("Case 30: !ispunct ('\\035')");
  }
  
  /* Case 31 */
  if (!(!ispunct ('\036'))) {
    failed ("Case 31: !ispunct ('\\036')");
  }
  
  /* Case 32 */
  if (!(!ispunct ('\037'))) {
    failed ("Case 32: !ispunct ('\\037')");
  }
  
  /* Case 33 */
  if (!(!ispunct (' '))) {
    failed ("Case 33: !ispunct (' ')");
  }
  
  /* Case 34 */
  if (!(ispunct ('!'))) {
    failed ("Case 34: ispunct ('!')");
  }
  
  /* Case 35 */
  if (!(ispunct ('\"'))) {
    failed ("Case 35: ispunct ('\\\"')");
  }
  
  /* Case 36 */
  if (!(ispunct ('#'))) {
    failed ("Case 36: ispunct ('#')");
  }
  
  /* Case 37 */
  if (!(ispunct ('$'))) {
    failed ("Case 37: ispunct ('$')");
  }
  
  /* Case 38 */
  if (!(ispunct ('%'))) {
    failed ("Case 38: ispunct ('%')");
  }
  
  /* Case 39 */
  if (!(ispunct ('&'))) {
    failed ("Case 39: ispunct ('&')");
  }
  
  /* Case 40 */
  if (!(ispunct ('\''))) {
    failed ("Case 40: ispunct ('\\'')");
  }
  
  /* Case 41 */
  if (!(ispunct ('('))) {
    failed ("Case 41: ispunct ('(')");
  }
  
  /* Case 42 */
  if (!(ispunct (')'))) {
    failed ("Case 42: ispunct (')')");
  }
  
  /* Case 43 */
  if (!(ispunct ('*'))) {
    failed ("Case 43: ispunct ('*')");
  }
  
  /* Case 44 */
  if (!(ispunct ('+'))) {
    failed ("Case 44: ispunct ('+')");
  }
  
  /* Case 45 */
  if (!(ispunct (','))) {
    failed ("Case 45: ispunct (',')");
  }
  
  /* Case 46 */
  if (!(ispunct ('-'))) {
    failed ("Case 46: ispunct ('-')");
  }
  
  /* Case 47 */
  if (!(ispunct ('.'))) {
    failed ("Case 47: ispunct ('.')");
  }
  
  /* Case 48 */
  if (!(ispunct ('/'))) {
    failed ("Case 48: ispunct ('/')");
  }
  
  /* Case 49 */
  if (!(!ispunct ('0'))) {
    failed ("Case 49: !ispunct ('0')");
  }
  
  /* Case 50 */
  if (!(!ispunct ('1'))) {
    failed ("Case 50: !ispunct ('1')");
  }
  
  /* Case 51 */
  if (!(!ispunct ('2'))) {
    failed ("Case 51: !ispunct ('2')");
  }
  
  /* Case 52 */
  if (!(!ispunct ('3'))) {
    failed ("Case 52: !ispunct ('3')");
  }
  
  /* Case 53 */
  if (!(!ispunct ('4'))) {
    failed ("Case 53: !ispunct ('4')");
  }
  
  /* Case 54 */
  if (!(!ispunct ('5'))) {
    failed ("Case 54: !ispunct ('5')");
  }
  
  /* Case 55 */
  if (!(!ispunct ('6'))) {
    failed ("Case 55: !ispunct ('6')");
  }
  
  /* Case 56 */
  if (!(!ispunct ('7'))) {
    failed ("Case 56: !ispunct ('7')");
  }
  
  /* Case 57 */
  if (!(!ispunct ('8'))) {
    failed ("Case 57: !ispunct ('8')");
  }
  
  /* Case 58 */
  if (!(!ispunct ('9'))) {
    failed ("Case 58: !ispunct ('9')");
  }
  
  /* Case 59 */
  if (!(ispunct (':'))) {
    failed ("Case 59: ispunct (':')");
  }
  
  /* Case 60 */
  if (!(ispunct (';'))) {
    failed ("Case 60: ispunct (';')");
  }
  
  /* Case 61 */
  if (!(ispunct ('<'))) {
    failed ("Case 61: ispunct ('<')");
  }
  
  /* Case 62 */
  if (!(ispunct ('='))) {
    failed ("Case 62: ispunct ('=')");
  }
  
  /* Case 63 */
  if (!(ispunct ('>'))) {
    failed ("Case 63: ispunct ('>')");
  }
  
  /* Case 64 */
  if (!(ispunct ('?'))) {
    failed ("Case 64: ispunct ('?')");
  }
  
  /* Case 65 */
  if (!(ispunct ('@'))) {
    failed ("Case 65: ispunct ('@')");
  }
  
  /* Case 66 */
  if (!(!ispunct ('A'))) {
    failed ("Case 66: !ispunct ('A')");
  }
  
  /* Case 67 */
  if (!(!ispunct ('B'))) {
    failed ("Case 67: !ispunct ('B')");
  }
  
  /* Case 68 */
  if (!(!ispunct ('C'))) {
    failed ("Case 68: !ispunct ('C')");
  }
  
  /* Case 69 */
  if (!(!ispunct ('D'))) {
    failed ("Case 69: !ispunct ('D')");
  }
  
  /* Case 70 */
  if (!(!ispunct ('E'))) {
    failed ("Case 70: !ispunct ('E')");
  }
  
  /* Case 71 */
  if (!(!ispunct ('F'))) {
    failed ("Case 71: !ispunct ('F')");
  }
  
  /* Case 72 */
  if (!(!ispunct ('G'))) {
    failed ("Case 72: !ispunct ('G')");
  }
  
  /* Case 73 */
  if (!(!ispunct ('H'))) {
    failed ("Case 73: !ispunct ('H')");
  }
  
  /* Case 74 */
  if (!(!ispunct ('I'))) {
    failed ("Case 74: !ispunct ('I')");
  }
  
  /* Case 75 */
  if (!(!ispunct ('J'))) {
    failed ("Case 75: !ispunct ('J')");
  }
  
  /* Case 76 */
  if (!(!ispunct ('K'))) {
    failed ("Case 76: !ispunct ('K')");
  }
  
  /* Case 77 */
  if (!(!ispunct ('L'))) {
    failed ("Case 77: !ispunct ('L')");
  }
  
  /* Case 78 */
  if (!(!ispunct ('M'))) {
    failed ("Case 78: !ispunct ('M')");
  }
  
  /* Case 79 */
  if (!(!ispunct ('N'))) {
    failed ("Case 79: !ispunct ('N')");
  }
  
  /* Case 80 */
  if (!(!ispunct ('O'))) {
    failed ("Case 80: !ispunct ('O')");
  }
  
  /* Case 81 */
  if (!(!ispunct ('P'))) {
    failed ("Case 81: !ispunct ('P')");
  }
  
  /* Case 82 */
  if (!(!ispunct ('Q'))) {
    failed ("Case 82: !ispunct ('Q')");
  }
  
  /* Case 83 */
  if (!(!ispunct ('R'))) {
    failed ("Case 83: !ispunct ('R')");
  }
  
  /* Case 84 */
  if (!(!ispunct ('S'))) {
    failed ("Case 84: !ispunct ('S')");
  }
  
  /* Case 85 */
  if (!(!ispunct ('T'))) {
    failed ("Case 85: !ispunct ('T')");
  }
  
  /* Case 86 */
  if (!(!ispunct ('U'))) {
    failed ("Case 86: !ispunct ('U')");
  }
  
  /* Case 87 */
  if (!(!ispunct ('V'))) {
    failed ("Case 87: !ispunct ('V')");
  }
  
  /* Case 88 */
  if (!(!ispunct ('W'))) {
    failed ("Case 88: !ispunct ('W')");
  }
  
  /* Case 89 */
  if (!(!ispunct ('X'))) {
    failed ("Case 89: !ispunct ('X')");
  }
  
  /* Case 90 */
  if (!(!ispunct ('Y'))) {
    failed ("Case 90: !ispunct ('Y')");
  }
  
  /* Case 91 */
  if (!(!ispunct ('Z'))) {
    failed ("Case 91: !ispunct ('Z')");
  }
  
  /* Case 92 */
  if (!(ispunct ('['))) {
    failed ("Case 92: ispunct ('[')");
  }
  
  /* Case 93 */
  if (!(ispunct ('\\'))) {
    failed ("Case 93: ispunct ('\\\\')");
  }
  
  /* Case 94 */
  if (!(ispunct (']'))) {
    failed ("Case 94: ispunct (']')");
  }
  
  /* Case 95 */
  if (!(ispunct ('^'))) {
    failed ("Case 95: ispunct ('^')");
  }
  
  /* Case 96 */
  if (!(ispunct ('_'))) {
    failed ("Case 96: ispunct ('_')");
  }
  
  /* Case 97 */
  if (!(ispunct ('`'))) {
    failed ("Case 97: ispunct ('`')");
  }
  
  /* Case 98 */
  if (!(!ispunct ('a'))) {
    failed ("Case 98: !ispunct ('a')");
  }
  
  /* Case 99 */
  if (!(!ispunct ('b'))) {
    failed ("Case 99: !ispunct ('b')");
  }
  
  /* Case 100 */
  if (!(!ispunct ('c'))) {
    failed ("Case 100: !ispunct ('c')");
  }
  
  /* Case 101 */
  if (!(!ispunct ('d'))) {
    failed ("Case 101: !ispunct ('d')");
  }
  
  /* Case 102 */
  if (!(!ispunct ('e'))) {
    failed ("Case 102: !ispunct ('e')");
  }
  
  /* Case 103 */
  if (!(!ispunct ('f'))) {
    failed ("Case 103: !ispunct ('f')");
  }
  
  /* Case 104 */
  if (!(!ispunct ('g'))) {
    failed ("Case 104: !ispunct ('g')");
  }
  
  /* Case 105 */
  if (!(!ispunct ('h'))) {
    failed ("Case 105: !ispunct ('h')");
  }
  
  /* Case 106 */
  if (!(!ispunct ('i'))) {
    failed ("Case 106: !ispunct ('i')");
  }
  
  /* Case 107 */
  if (!(!ispunct ('j'))) {
    failed ("Case 107: !ispunct ('j')");
  }
  
  /* Case 108 */
  if (!(!ispunct ('k'))) {
    failed ("Case 108: !ispunct ('k')");
  }
  
  /* Case 109 */
  if (!(!ispunct ('l'))) {
    failed ("Case 109: !ispunct ('l')");
  }
  
  /* Case 110 */
  if (!(!ispunct ('m'))) {
    failed ("Case 110: !ispunct ('m')");
  }
  
  /* Case 111 */
  if (!(!ispunct ('n'))) {
    failed ("Case 111: !ispunct ('n')");
  }
  
  /* Case 112 */
  if (!(!ispunct ('o'))) {
    failed ("Case 112: !ispunct ('o')");
  }
  
  /* Case 113 */
  if (!(!ispunct ('p'))) {
    failed ("Case 113: !ispunct ('p')");
  }
  
  /* Case 114 */
  if (!(!ispunct ('q'))) {
    failed ("Case 114: !ispunct ('q')");
  }
  
  /* Case 115 */
  if (!(!ispunct ('r'))) {
    failed ("Case 115: !ispunct ('r')");
  }
  
  /* Case 116 */
  if (!(!ispunct ('s'))) {
    failed ("Case 116: !ispunct ('s')");
  }
  
  /* Case 117 */
  if (!(!ispunct ('t'))) {
    failed ("Case 117: !ispunct ('t')");
  }
  
  /* Case 118 */
  if (!(!ispunct ('u'))) {
    failed ("Case 118: !ispunct ('u')");
  }
  
  /* Case 119 */
  if (!(!ispunct ('v'))) {
    failed ("Case 119: !ispunct ('v')");
  }
  
  /* Case 120 */
  if (!(!ispunct ('w'))) {
    failed ("Case 120: !ispunct ('w')");
  }
  
  /* Case 121 */
  if (!(!ispunct ('x'))) {
    failed ("Case 121: !ispunct ('x')");
  }
  
  /* Case 122 */
  if (!(!ispunct ('y'))) {
    failed ("Case 122: !ispunct ('y')");
  }
  
  /* Case 123 */
  if (!(!ispunct ('z'))) {
    failed ("Case 123: !ispunct ('z')");
  }
  
  /* Case 124 */
  if (!(ispunct ('{'))) {
    failed ("Case 124: ispunct ('{')");
  }
  
  /* Case 125 */
  if (!(ispunct ('|'))) {
    failed ("Case 125: ispunct ('|')");
  }
  
  /* Case 126 */
  if (!(ispunct ('}'))) {
    failed ("Case 126: ispunct ('}')");
  }
  
  /* Case 127 */
  if (!(ispunct ('~'))) {
    failed ("Case 127: ispunct ('~')");
  }
  
  /* Case 128 */
  if (!(!ispunct ('\177'))) {
    failed ("Case 128: !ispunct ('\\177')");
  }
  
}


void main ()
{
  test ("test-ispunct", "Test for ANSI Standard C: 7.3.1.8");

  do_test ();

  result ();
}

