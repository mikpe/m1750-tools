/*
 * Test for ANSI Standard C: 7.3.1.6
 * 
 * #include <ctype.h>
 * int islower (int c);
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


static char *_test_islower_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(!islower ('\000'))) {
    failed ("Case 1: !islower ('\\000')");
  }
  
  /* Case 2 */
  if (!(!islower ('\001'))) {
    failed ("Case 2: !islower ('\\001')");
  }
  
  /* Case 3 */
  if (!(!islower ('\002'))) {
    failed ("Case 3: !islower ('\\002')");
  }
  
  /* Case 4 */
  if (!(!islower ('\003'))) {
    failed ("Case 4: !islower ('\\003')");
  }
  
  /* Case 5 */
  if (!(!islower ('\004'))) {
    failed ("Case 5: !islower ('\\004')");
  }
  
  /* Case 6 */
  if (!(!islower ('\005'))) {
    failed ("Case 6: !islower ('\\005')");
  }
  
  /* Case 7 */
  if (!(!islower ('\006'))) {
    failed ("Case 7: !islower ('\\006')");
  }
  
  /* Case 8 */
  if (!(!islower ('\007'))) {
    failed ("Case 8: !islower ('\\007')");
  }
  
  /* Case 9 */
  if (!(!islower ('\010'))) {
    failed ("Case 9: !islower ('\\010')");
  }
  
  /* Case 10 */
  if (!(!islower ('\011'))) {
    failed ("Case 10: !islower ('\\011')");
  }
  
  /* Case 11 */
  if (!(!islower ('\012'))) {
    failed ("Case 11: !islower ('\\012')");
  }
  
  /* Case 12 */
  if (!(!islower ('\013'))) {
    failed ("Case 12: !islower ('\\013')");
  }
  
  /* Case 13 */
  if (!(!islower ('\014'))) {
    failed ("Case 13: !islower ('\\014')");
  }
  
  /* Case 14 */
  if (!(!islower ('\015'))) {
    failed ("Case 14: !islower ('\\015')");
  }
  
  /* Case 15 */
  if (!(!islower ('\016'))) {
    failed ("Case 15: !islower ('\\016')");
  }
  
  /* Case 16 */
  if (!(!islower ('\017'))) {
    failed ("Case 16: !islower ('\\017')");
  }
  
  /* Case 17 */
  if (!(!islower ('\020'))) {
    failed ("Case 17: !islower ('\\020')");
  }
  
  /* Case 18 */
  if (!(!islower ('\021'))) {
    failed ("Case 18: !islower ('\\021')");
  }
  
  /* Case 19 */
  if (!(!islower ('\022'))) {
    failed ("Case 19: !islower ('\\022')");
  }
  
  /* Case 20 */
  if (!(!islower ('\023'))) {
    failed ("Case 20: !islower ('\\023')");
  }
  
  /* Case 21 */
  if (!(!islower ('\024'))) {
    failed ("Case 21: !islower ('\\024')");
  }
  
  /* Case 22 */
  if (!(!islower ('\025'))) {
    failed ("Case 22: !islower ('\\025')");
  }
  
  /* Case 23 */
  if (!(!islower ('\026'))) {
    failed ("Case 23: !islower ('\\026')");
  }
  
  /* Case 24 */
  if (!(!islower ('\027'))) {
    failed ("Case 24: !islower ('\\027')");
  }
  
  /* Case 25 */
  if (!(!islower ('\030'))) {
    failed ("Case 25: !islower ('\\030')");
  }
  
  /* Case 26 */
  if (!(!islower ('\031'))) {
    failed ("Case 26: !islower ('\\031')");
  }
  
  /* Case 27 */
  if (!(!islower ('\032'))) {
    failed ("Case 27: !islower ('\\032')");
  }
  
  /* Case 28 */
  if (!(!islower ('\033'))) {
    failed ("Case 28: !islower ('\\033')");
  }
  
  /* Case 29 */
  if (!(!islower ('\034'))) {
    failed ("Case 29: !islower ('\\034')");
  }
  
  /* Case 30 */
  if (!(!islower ('\035'))) {
    failed ("Case 30: !islower ('\\035')");
  }
  
  /* Case 31 */
  if (!(!islower ('\036'))) {
    failed ("Case 31: !islower ('\\036')");
  }
  
  /* Case 32 */
  if (!(!islower ('\037'))) {
    failed ("Case 32: !islower ('\\037')");
  }
  
  /* Case 33 */
  if (!(!islower (' '))) {
    failed ("Case 33: !islower (' ')");
  }
  
  /* Case 34 */
  if (!(!islower ('!'))) {
    failed ("Case 34: !islower ('!')");
  }
  
  /* Case 35 */
  if (!(!islower ('\"'))) {
    failed ("Case 35: !islower ('\\\"')");
  }
  
  /* Case 36 */
  if (!(!islower ('#'))) {
    failed ("Case 36: !islower ('#')");
  }
  
  /* Case 37 */
  if (!(!islower ('$'))) {
    failed ("Case 37: !islower ('$')");
  }
  
  /* Case 38 */
  if (!(!islower ('%'))) {
    failed ("Case 38: !islower ('%')");
  }
  
  /* Case 39 */
  if (!(!islower ('&'))) {
    failed ("Case 39: !islower ('&')");
  }
  
  /* Case 40 */
  if (!(!islower ('\''))) {
    failed ("Case 40: !islower ('\\'')");
  }
  
  /* Case 41 */
  if (!(!islower ('('))) {
    failed ("Case 41: !islower ('(')");
  }
  
  /* Case 42 */
  if (!(!islower (')'))) {
    failed ("Case 42: !islower (')')");
  }
  
  /* Case 43 */
  if (!(!islower ('*'))) {
    failed ("Case 43: !islower ('*')");
  }
  
  /* Case 44 */
  if (!(!islower ('+'))) {
    failed ("Case 44: !islower ('+')");
  }
  
  /* Case 45 */
  if (!(!islower (','))) {
    failed ("Case 45: !islower (',')");
  }
  
  /* Case 46 */
  if (!(!islower ('-'))) {
    failed ("Case 46: !islower ('-')");
  }
  
  /* Case 47 */
  if (!(!islower ('.'))) {
    failed ("Case 47: !islower ('.')");
  }
  
  /* Case 48 */
  if (!(!islower ('/'))) {
    failed ("Case 48: !islower ('/')");
  }
  
  /* Case 49 */
  if (!(!islower ('0'))) {
    failed ("Case 49: !islower ('0')");
  }
  
  /* Case 50 */
  if (!(!islower ('1'))) {
    failed ("Case 50: !islower ('1')");
  }
  
  /* Case 51 */
  if (!(!islower ('2'))) {
    failed ("Case 51: !islower ('2')");
  }
  
  /* Case 52 */
  if (!(!islower ('3'))) {
    failed ("Case 52: !islower ('3')");
  }
  
  /* Case 53 */
  if (!(!islower ('4'))) {
    failed ("Case 53: !islower ('4')");
  }
  
  /* Case 54 */
  if (!(!islower ('5'))) {
    failed ("Case 54: !islower ('5')");
  }
  
  /* Case 55 */
  if (!(!islower ('6'))) {
    failed ("Case 55: !islower ('6')");
  }
  
  /* Case 56 */
  if (!(!islower ('7'))) {
    failed ("Case 56: !islower ('7')");
  }
  
  /* Case 57 */
  if (!(!islower ('8'))) {
    failed ("Case 57: !islower ('8')");
  }
  
  /* Case 58 */
  if (!(!islower ('9'))) {
    failed ("Case 58: !islower ('9')");
  }
  
  /* Case 59 */
  if (!(!islower (':'))) {
    failed ("Case 59: !islower (':')");
  }
  
  /* Case 60 */
  if (!(!islower (';'))) {
    failed ("Case 60: !islower (';')");
  }
  
  /* Case 61 */
  if (!(!islower ('<'))) {
    failed ("Case 61: !islower ('<')");
  }
  
  /* Case 62 */
  if (!(!islower ('='))) {
    failed ("Case 62: !islower ('=')");
  }
  
  /* Case 63 */
  if (!(!islower ('>'))) {
    failed ("Case 63: !islower ('>')");
  }
  
  /* Case 64 */
  if (!(!islower ('?'))) {
    failed ("Case 64: !islower ('?')");
  }
  
  /* Case 65 */
  if (!(!islower ('@'))) {
    failed ("Case 65: !islower ('@')");
  }
  
  /* Case 66 */
  if (!(!islower ('A'))) {
    failed ("Case 66: !islower ('A')");
  }
  
  /* Case 67 */
  if (!(!islower ('B'))) {
    failed ("Case 67: !islower ('B')");
  }
  
  /* Case 68 */
  if (!(!islower ('C'))) {
    failed ("Case 68: !islower ('C')");
  }
  
  /* Case 69 */
  if (!(!islower ('D'))) {
    failed ("Case 69: !islower ('D')");
  }
  
  /* Case 70 */
  if (!(!islower ('E'))) {
    failed ("Case 70: !islower ('E')");
  }
  
  /* Case 71 */
  if (!(!islower ('F'))) {
    failed ("Case 71: !islower ('F')");
  }
  
  /* Case 72 */
  if (!(!islower ('G'))) {
    failed ("Case 72: !islower ('G')");
  }
  
  /* Case 73 */
  if (!(!islower ('H'))) {
    failed ("Case 73: !islower ('H')");
  }
  
  /* Case 74 */
  if (!(!islower ('I'))) {
    failed ("Case 74: !islower ('I')");
  }
  
  /* Case 75 */
  if (!(!islower ('J'))) {
    failed ("Case 75: !islower ('J')");
  }
  
  /* Case 76 */
  if (!(!islower ('K'))) {
    failed ("Case 76: !islower ('K')");
  }
  
  /* Case 77 */
  if (!(!islower ('L'))) {
    failed ("Case 77: !islower ('L')");
  }
  
  /* Case 78 */
  if (!(!islower ('M'))) {
    failed ("Case 78: !islower ('M')");
  }
  
  /* Case 79 */
  if (!(!islower ('N'))) {
    failed ("Case 79: !islower ('N')");
  }
  
  /* Case 80 */
  if (!(!islower ('O'))) {
    failed ("Case 80: !islower ('O')");
  }
  
  /* Case 81 */
  if (!(!islower ('P'))) {
    failed ("Case 81: !islower ('P')");
  }
  
  /* Case 82 */
  if (!(!islower ('Q'))) {
    failed ("Case 82: !islower ('Q')");
  }
  
  /* Case 83 */
  if (!(!islower ('R'))) {
    failed ("Case 83: !islower ('R')");
  }
  
  /* Case 84 */
  if (!(!islower ('S'))) {
    failed ("Case 84: !islower ('S')");
  }
  
  /* Case 85 */
  if (!(!islower ('T'))) {
    failed ("Case 85: !islower ('T')");
  }
  
  /* Case 86 */
  if (!(!islower ('U'))) {
    failed ("Case 86: !islower ('U')");
  }
  
  /* Case 87 */
  if (!(!islower ('V'))) {
    failed ("Case 87: !islower ('V')");
  }
  
  /* Case 88 */
  if (!(!islower ('W'))) {
    failed ("Case 88: !islower ('W')");
  }
  
  /* Case 89 */
  if (!(!islower ('X'))) {
    failed ("Case 89: !islower ('X')");
  }
  
  /* Case 90 */
  if (!(!islower ('Y'))) {
    failed ("Case 90: !islower ('Y')");
  }
  
  /* Case 91 */
  if (!(!islower ('Z'))) {
    failed ("Case 91: !islower ('Z')");
  }
  
  /* Case 92 */
  if (!(!islower ('['))) {
    failed ("Case 92: !islower ('[')");
  }
  
  /* Case 93 */
  if (!(!islower ('\\'))) {
    failed ("Case 93: !islower ('\\\\')");
  }
  
  /* Case 94 */
  if (!(!islower (']'))) {
    failed ("Case 94: !islower (']')");
  }
  
  /* Case 95 */
  if (!(!islower ('^'))) {
    failed ("Case 95: !islower ('^')");
  }
  
  /* Case 96 */
  if (!(!islower ('_'))) {
    failed ("Case 96: !islower ('_')");
  }
  
  /* Case 97 */
  if (!(!islower ('`'))) {
    failed ("Case 97: !islower ('`')");
  }
  
  /* Case 98 */
  if (!(islower ('a'))) {
    failed ("Case 98: islower ('a')");
  }
  
  /* Case 99 */
  if (!(islower ('b'))) {
    failed ("Case 99: islower ('b')");
  }
  
  /* Case 100 */
  if (!(islower ('c'))) {
    failed ("Case 100: islower ('c')");
  }
  
  /* Case 101 */
  if (!(islower ('d'))) {
    failed ("Case 101: islower ('d')");
  }
  
  /* Case 102 */
  if (!(islower ('e'))) {
    failed ("Case 102: islower ('e')");
  }
  
  /* Case 103 */
  if (!(islower ('f'))) {
    failed ("Case 103: islower ('f')");
  }
  
  /* Case 104 */
  if (!(islower ('g'))) {
    failed ("Case 104: islower ('g')");
  }
  
  /* Case 105 */
  if (!(islower ('h'))) {
    failed ("Case 105: islower ('h')");
  }
  
  /* Case 106 */
  if (!(islower ('i'))) {
    failed ("Case 106: islower ('i')");
  }
  
  /* Case 107 */
  if (!(islower ('j'))) {
    failed ("Case 107: islower ('j')");
  }
  
  /* Case 108 */
  if (!(islower ('k'))) {
    failed ("Case 108: islower ('k')");
  }
  
  /* Case 109 */
  if (!(islower ('l'))) {
    failed ("Case 109: islower ('l')");
  }
  
  /* Case 110 */
  if (!(islower ('m'))) {
    failed ("Case 110: islower ('m')");
  }
  
  /* Case 111 */
  if (!(islower ('n'))) {
    failed ("Case 111: islower ('n')");
  }
  
  /* Case 112 */
  if (!(islower ('o'))) {
    failed ("Case 112: islower ('o')");
  }
  
  /* Case 113 */
  if (!(islower ('p'))) {
    failed ("Case 113: islower ('p')");
  }
  
  /* Case 114 */
  if (!(islower ('q'))) {
    failed ("Case 114: islower ('q')");
  }
  
  /* Case 115 */
  if (!(islower ('r'))) {
    failed ("Case 115: islower ('r')");
  }
  
  /* Case 116 */
  if (!(islower ('s'))) {
    failed ("Case 116: islower ('s')");
  }
  
  /* Case 117 */
  if (!(islower ('t'))) {
    failed ("Case 117: islower ('t')");
  }
  
  /* Case 118 */
  if (!(islower ('u'))) {
    failed ("Case 118: islower ('u')");
  }
  
  /* Case 119 */
  if (!(islower ('v'))) {
    failed ("Case 119: islower ('v')");
  }
  
  /* Case 120 */
  if (!(islower ('w'))) {
    failed ("Case 120: islower ('w')");
  }
  
  /* Case 121 */
  if (!(islower ('x'))) {
    failed ("Case 121: islower ('x')");
  }
  
  /* Case 122 */
  if (!(islower ('y'))) {
    failed ("Case 122: islower ('y')");
  }
  
  /* Case 123 */
  if (!(islower ('z'))) {
    failed ("Case 123: islower ('z')");
  }
  
  /* Case 124 */
  if (!(!islower ('{'))) {
    failed ("Case 124: !islower ('{')");
  }
  
  /* Case 125 */
  if (!(!islower ('|'))) {
    failed ("Case 125: !islower ('|')");
  }
  
  /* Case 126 */
  if (!(!islower ('}'))) {
    failed ("Case 126: !islower ('}')");
  }
  
  /* Case 127 */
  if (!(!islower ('~'))) {
    failed ("Case 127: !islower ('~')");
  }
  
  /* Case 128 */
  if (!(!islower ('\177'))) {
    failed ("Case 128: !islower ('\\177')");
  }
  
}


void main ()
{
  test ("test-islower", "Test for ANSI Standard C: 7.3.1.6");

  do_test ();

  result ();
}

