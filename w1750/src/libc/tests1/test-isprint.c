/*
 * Test for ANSI Standard C: 7.3.1.7
 * 
 * #include <ctype.h>
 * int isprint (int c);
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


static char *_test_isprint_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(!isprint ('\000'))) {
    failed ("Case 1: !isprint ('\\000')");
  }
  
  /* Case 2 */
  if (!(!isprint ('\001'))) {
    failed ("Case 2: !isprint ('\\001')");
  }
  
  /* Case 3 */
  if (!(!isprint ('\002'))) {
    failed ("Case 3: !isprint ('\\002')");
  }
  
  /* Case 4 */
  if (!(!isprint ('\003'))) {
    failed ("Case 4: !isprint ('\\003')");
  }
  
  /* Case 5 */
  if (!(!isprint ('\004'))) {
    failed ("Case 5: !isprint ('\\004')");
  }
  
  /* Case 6 */
  if (!(!isprint ('\005'))) {
    failed ("Case 6: !isprint ('\\005')");
  }
  
  /* Case 7 */
  if (!(!isprint ('\006'))) {
    failed ("Case 7: !isprint ('\\006')");
  }
  
  /* Case 8 */
  if (!(!isprint ('\007'))) {
    failed ("Case 8: !isprint ('\\007')");
  }
  
  /* Case 9 */
  if (!(!isprint ('\010'))) {
    failed ("Case 9: !isprint ('\\010')");
  }
  
  /* Case 10 */
  if (!(!isprint ('\011'))) {
    failed ("Case 10: !isprint ('\\011')");
  }
  
  /* Case 11 */
  if (!(!isprint ('\012'))) {
    failed ("Case 11: !isprint ('\\012')");
  }
  
  /* Case 12 */
  if (!(!isprint ('\013'))) {
    failed ("Case 12: !isprint ('\\013')");
  }
  
  /* Case 13 */
  if (!(!isprint ('\014'))) {
    failed ("Case 13: !isprint ('\\014')");
  }
  
  /* Case 14 */
  if (!(!isprint ('\015'))) {
    failed ("Case 14: !isprint ('\\015')");
  }
  
  /* Case 15 */
  if (!(!isprint ('\016'))) {
    failed ("Case 15: !isprint ('\\016')");
  }
  
  /* Case 16 */
  if (!(!isprint ('\017'))) {
    failed ("Case 16: !isprint ('\\017')");
  }
  
  /* Case 17 */
  if (!(!isprint ('\020'))) {
    failed ("Case 17: !isprint ('\\020')");
  }
  
  /* Case 18 */
  if (!(!isprint ('\021'))) {
    failed ("Case 18: !isprint ('\\021')");
  }
  
  /* Case 19 */
  if (!(!isprint ('\022'))) {
    failed ("Case 19: !isprint ('\\022')");
  }
  
  /* Case 20 */
  if (!(!isprint ('\023'))) {
    failed ("Case 20: !isprint ('\\023')");
  }
  
  /* Case 21 */
  if (!(!isprint ('\024'))) {
    failed ("Case 21: !isprint ('\\024')");
  }
  
  /* Case 22 */
  if (!(!isprint ('\025'))) {
    failed ("Case 22: !isprint ('\\025')");
  }
  
  /* Case 23 */
  if (!(!isprint ('\026'))) {
    failed ("Case 23: !isprint ('\\026')");
  }
  
  /* Case 24 */
  if (!(!isprint ('\027'))) {
    failed ("Case 24: !isprint ('\\027')");
  }
  
  /* Case 25 */
  if (!(!isprint ('\030'))) {
    failed ("Case 25: !isprint ('\\030')");
  }
  
  /* Case 26 */
  if (!(!isprint ('\031'))) {
    failed ("Case 26: !isprint ('\\031')");
  }
  
  /* Case 27 */
  if (!(!isprint ('\032'))) {
    failed ("Case 27: !isprint ('\\032')");
  }
  
  /* Case 28 */
  if (!(!isprint ('\033'))) {
    failed ("Case 28: !isprint ('\\033')");
  }
  
  /* Case 29 */
  if (!(!isprint ('\034'))) {
    failed ("Case 29: !isprint ('\\034')");
  }
  
  /* Case 30 */
  if (!(!isprint ('\035'))) {
    failed ("Case 30: !isprint ('\\035')");
  }
  
  /* Case 31 */
  if (!(!isprint ('\036'))) {
    failed ("Case 31: !isprint ('\\036')");
  }
  
  /* Case 32 */
  if (!(!isprint ('\037'))) {
    failed ("Case 32: !isprint ('\\037')");
  }
  
  /* Case 33 */
  if (!(isprint (' '))) {
    failed ("Case 33: isprint (' ')");
  }
  
  /* Case 34 */
  if (!(isprint ('!'))) {
    failed ("Case 34: isprint ('!')");
  }
  
  /* Case 35 */
  if (!(isprint ('\"'))) {
    failed ("Case 35: isprint ('\\\"')");
  }
  
  /* Case 36 */
  if (!(isprint ('#'))) {
    failed ("Case 36: isprint ('#')");
  }
  
  /* Case 37 */
  if (!(isprint ('$'))) {
    failed ("Case 37: isprint ('$')");
  }
  
  /* Case 38 */
  if (!(isprint ('%'))) {
    failed ("Case 38: isprint ('%')");
  }
  
  /* Case 39 */
  if (!(isprint ('&'))) {
    failed ("Case 39: isprint ('&')");
  }
  
  /* Case 40 */
  if (!(isprint ('\''))) {
    failed ("Case 40: isprint ('\\'')");
  }
  
  /* Case 41 */
  if (!(isprint ('('))) {
    failed ("Case 41: isprint ('(')");
  }
  
  /* Case 42 */
  if (!(isprint (')'))) {
    failed ("Case 42: isprint (')')");
  }
  
  /* Case 43 */
  if (!(isprint ('*'))) {
    failed ("Case 43: isprint ('*')");
  }
  
  /* Case 44 */
  if (!(isprint ('+'))) {
    failed ("Case 44: isprint ('+')");
  }
  
  /* Case 45 */
  if (!(isprint (','))) {
    failed ("Case 45: isprint (',')");
  }
  
  /* Case 46 */
  if (!(isprint ('-'))) {
    failed ("Case 46: isprint ('-')");
  }
  
  /* Case 47 */
  if (!(isprint ('.'))) {
    failed ("Case 47: isprint ('.')");
  }
  
  /* Case 48 */
  if (!(isprint ('/'))) {
    failed ("Case 48: isprint ('/')");
  }
  
  /* Case 49 */
  if (!(isprint ('0'))) {
    failed ("Case 49: isprint ('0')");
  }
  
  /* Case 50 */
  if (!(isprint ('1'))) {
    failed ("Case 50: isprint ('1')");
  }
  
  /* Case 51 */
  if (!(isprint ('2'))) {
    failed ("Case 51: isprint ('2')");
  }
  
  /* Case 52 */
  if (!(isprint ('3'))) {
    failed ("Case 52: isprint ('3')");
  }
  
  /* Case 53 */
  if (!(isprint ('4'))) {
    failed ("Case 53: isprint ('4')");
  }
  
  /* Case 54 */
  if (!(isprint ('5'))) {
    failed ("Case 54: isprint ('5')");
  }
  
  /* Case 55 */
  if (!(isprint ('6'))) {
    failed ("Case 55: isprint ('6')");
  }
  
  /* Case 56 */
  if (!(isprint ('7'))) {
    failed ("Case 56: isprint ('7')");
  }
  
  /* Case 57 */
  if (!(isprint ('8'))) {
    failed ("Case 57: isprint ('8')");
  }
  
  /* Case 58 */
  if (!(isprint ('9'))) {
    failed ("Case 58: isprint ('9')");
  }
  
  /* Case 59 */
  if (!(isprint (':'))) {
    failed ("Case 59: isprint (':')");
  }
  
  /* Case 60 */
  if (!(isprint (';'))) {
    failed ("Case 60: isprint (';')");
  }
  
  /* Case 61 */
  if (!(isprint ('<'))) {
    failed ("Case 61: isprint ('<')");
  }
  
  /* Case 62 */
  if (!(isprint ('='))) {
    failed ("Case 62: isprint ('=')");
  }
  
  /* Case 63 */
  if (!(isprint ('>'))) {
    failed ("Case 63: isprint ('>')");
  }
  
  /* Case 64 */
  if (!(isprint ('?'))) {
    failed ("Case 64: isprint ('?')");
  }
  
  /* Case 65 */
  if (!(isprint ('@'))) {
    failed ("Case 65: isprint ('@')");
  }
  
  /* Case 66 */
  if (!(isprint ('A'))) {
    failed ("Case 66: isprint ('A')");
  }
  
  /* Case 67 */
  if (!(isprint ('B'))) {
    failed ("Case 67: isprint ('B')");
  }
  
  /* Case 68 */
  if (!(isprint ('C'))) {
    failed ("Case 68: isprint ('C')");
  }
  
  /* Case 69 */
  if (!(isprint ('D'))) {
    failed ("Case 69: isprint ('D')");
  }
  
  /* Case 70 */
  if (!(isprint ('E'))) {
    failed ("Case 70: isprint ('E')");
  }
  
  /* Case 71 */
  if (!(isprint ('F'))) {
    failed ("Case 71: isprint ('F')");
  }
  
  /* Case 72 */
  if (!(isprint ('G'))) {
    failed ("Case 72: isprint ('G')");
  }
  
  /* Case 73 */
  if (!(isprint ('H'))) {
    failed ("Case 73: isprint ('H')");
  }
  
  /* Case 74 */
  if (!(isprint ('I'))) {
    failed ("Case 74: isprint ('I')");
  }
  
  /* Case 75 */
  if (!(isprint ('J'))) {
    failed ("Case 75: isprint ('J')");
  }
  
  /* Case 76 */
  if (!(isprint ('K'))) {
    failed ("Case 76: isprint ('K')");
  }
  
  /* Case 77 */
  if (!(isprint ('L'))) {
    failed ("Case 77: isprint ('L')");
  }
  
  /* Case 78 */
  if (!(isprint ('M'))) {
    failed ("Case 78: isprint ('M')");
  }
  
  /* Case 79 */
  if (!(isprint ('N'))) {
    failed ("Case 79: isprint ('N')");
  }
  
  /* Case 80 */
  if (!(isprint ('O'))) {
    failed ("Case 80: isprint ('O')");
  }
  
  /* Case 81 */
  if (!(isprint ('P'))) {
    failed ("Case 81: isprint ('P')");
  }
  
  /* Case 82 */
  if (!(isprint ('Q'))) {
    failed ("Case 82: isprint ('Q')");
  }
  
  /* Case 83 */
  if (!(isprint ('R'))) {
    failed ("Case 83: isprint ('R')");
  }
  
  /* Case 84 */
  if (!(isprint ('S'))) {
    failed ("Case 84: isprint ('S')");
  }
  
  /* Case 85 */
  if (!(isprint ('T'))) {
    failed ("Case 85: isprint ('T')");
  }
  
  /* Case 86 */
  if (!(isprint ('U'))) {
    failed ("Case 86: isprint ('U')");
  }
  
  /* Case 87 */
  if (!(isprint ('V'))) {
    failed ("Case 87: isprint ('V')");
  }
  
  /* Case 88 */
  if (!(isprint ('W'))) {
    failed ("Case 88: isprint ('W')");
  }
  
  /* Case 89 */
  if (!(isprint ('X'))) {
    failed ("Case 89: isprint ('X')");
  }
  
  /* Case 90 */
  if (!(isprint ('Y'))) {
    failed ("Case 90: isprint ('Y')");
  }
  
  /* Case 91 */
  if (!(isprint ('Z'))) {
    failed ("Case 91: isprint ('Z')");
  }
  
  /* Case 92 */
  if (!(isprint ('['))) {
    failed ("Case 92: isprint ('[')");
  }
  
  /* Case 93 */
  if (!(isprint ('\\'))) {
    failed ("Case 93: isprint ('\\\\')");
  }
  
  /* Case 94 */
  if (!(isprint (']'))) {
    failed ("Case 94: isprint (']')");
  }
  
  /* Case 95 */
  if (!(isprint ('^'))) {
    failed ("Case 95: isprint ('^')");
  }
  
  /* Case 96 */
  if (!(isprint ('_'))) {
    failed ("Case 96: isprint ('_')");
  }
  
  /* Case 97 */
  if (!(isprint ('`'))) {
    failed ("Case 97: isprint ('`')");
  }
  
  /* Case 98 */
  if (!(isprint ('a'))) {
    failed ("Case 98: isprint ('a')");
  }
  
  /* Case 99 */
  if (!(isprint ('b'))) {
    failed ("Case 99: isprint ('b')");
  }
  
  /* Case 100 */
  if (!(isprint ('c'))) {
    failed ("Case 100: isprint ('c')");
  }
  
  /* Case 101 */
  if (!(isprint ('d'))) {
    failed ("Case 101: isprint ('d')");
  }
  
  /* Case 102 */
  if (!(isprint ('e'))) {
    failed ("Case 102: isprint ('e')");
  }
  
  /* Case 103 */
  if (!(isprint ('f'))) {
    failed ("Case 103: isprint ('f')");
  }
  
  /* Case 104 */
  if (!(isprint ('g'))) {
    failed ("Case 104: isprint ('g')");
  }
  
  /* Case 105 */
  if (!(isprint ('h'))) {
    failed ("Case 105: isprint ('h')");
  }
  
  /* Case 106 */
  if (!(isprint ('i'))) {
    failed ("Case 106: isprint ('i')");
  }
  
  /* Case 107 */
  if (!(isprint ('j'))) {
    failed ("Case 107: isprint ('j')");
  }
  
  /* Case 108 */
  if (!(isprint ('k'))) {
    failed ("Case 108: isprint ('k')");
  }
  
  /* Case 109 */
  if (!(isprint ('l'))) {
    failed ("Case 109: isprint ('l')");
  }
  
  /* Case 110 */
  if (!(isprint ('m'))) {
    failed ("Case 110: isprint ('m')");
  }
  
  /* Case 111 */
  if (!(isprint ('n'))) {
    failed ("Case 111: isprint ('n')");
  }
  
  /* Case 112 */
  if (!(isprint ('o'))) {
    failed ("Case 112: isprint ('o')");
  }
  
  /* Case 113 */
  if (!(isprint ('p'))) {
    failed ("Case 113: isprint ('p')");
  }
  
  /* Case 114 */
  if (!(isprint ('q'))) {
    failed ("Case 114: isprint ('q')");
  }
  
  /* Case 115 */
  if (!(isprint ('r'))) {
    failed ("Case 115: isprint ('r')");
  }
  
  /* Case 116 */
  if (!(isprint ('s'))) {
    failed ("Case 116: isprint ('s')");
  }
  
  /* Case 117 */
  if (!(isprint ('t'))) {
    failed ("Case 117: isprint ('t')");
  }
  
  /* Case 118 */
  if (!(isprint ('u'))) {
    failed ("Case 118: isprint ('u')");
  }
  
  /* Case 119 */
  if (!(isprint ('v'))) {
    failed ("Case 119: isprint ('v')");
  }
  
  /* Case 120 */
  if (!(isprint ('w'))) {
    failed ("Case 120: isprint ('w')");
  }
  
  /* Case 121 */
  if (!(isprint ('x'))) {
    failed ("Case 121: isprint ('x')");
  }
  
  /* Case 122 */
  if (!(isprint ('y'))) {
    failed ("Case 122: isprint ('y')");
  }
  
  /* Case 123 */
  if (!(isprint ('z'))) {
    failed ("Case 123: isprint ('z')");
  }
  
  /* Case 124 */
  if (!(isprint ('{'))) {
    failed ("Case 124: isprint ('{')");
  }
  
  /* Case 125 */
  if (!(isprint ('|'))) {
    failed ("Case 125: isprint ('|')");
  }
  
  /* Case 126 */
  if (!(isprint ('}'))) {
    failed ("Case 126: isprint ('}')");
  }
  
  /* Case 127 */
  if (!(isprint ('~'))) {
    failed ("Case 127: isprint ('~')");
  }
  
  /* Case 128 */
  if (!(!isprint ('\177'))) {
    failed ("Case 128: !isprint ('\\177')");
  }
  
}


void main ()
{
  test ("test-isprint", "Test for ANSI Standard C: 7.3.1.7");

  do_test ();

  result ();
}

