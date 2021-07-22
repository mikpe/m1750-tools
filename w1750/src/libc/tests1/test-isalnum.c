/*
 * Test for ANSI Standard C: 7.3.1.1
 * 
 * #include <ctype.h>
 * int isalnum (int c);
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


static char *_test_isalnum_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(!isalnum ('\000'))) {
    failed ("Case 1: !isalnum ('\\000')");
  }
  
  /* Case 2 */
  if (!(!isalnum ('\001'))) {
    failed ("Case 2: !isalnum ('\\001')");
  }
  
  /* Case 3 */
  if (!(!isalnum ('\002'))) {
    failed ("Case 3: !isalnum ('\\002')");
  }
  
  /* Case 4 */
  if (!(!isalnum ('\003'))) {
    failed ("Case 4: !isalnum ('\\003')");
  }
  
  /* Case 5 */
  if (!(!isalnum ('\004'))) {
    failed ("Case 5: !isalnum ('\\004')");
  }
  
  /* Case 6 */
  if (!(!isalnum ('\005'))) {
    failed ("Case 6: !isalnum ('\\005')");
  }
  
  /* Case 7 */
  if (!(!isalnum ('\006'))) {
    failed ("Case 7: !isalnum ('\\006')");
  }
  
  /* Case 8 */
  if (!(!isalnum ('\007'))) {
    failed ("Case 8: !isalnum ('\\007')");
  }
  
  /* Case 9 */
  if (!(!isalnum ('\010'))) {
    failed ("Case 9: !isalnum ('\\010')");
  }
  
  /* Case 10 */
  if (!(!isalnum ('\011'))) {
    failed ("Case 10: !isalnum ('\\011')");
  }
  
  /* Case 11 */
  if (!(!isalnum ('\012'))) {
    failed ("Case 11: !isalnum ('\\012')");
  }
  
  /* Case 12 */
  if (!(!isalnum ('\013'))) {
    failed ("Case 12: !isalnum ('\\013')");
  }
  
  /* Case 13 */
  if (!(!isalnum ('\014'))) {
    failed ("Case 13: !isalnum ('\\014')");
  }
  
  /* Case 14 */
  if (!(!isalnum ('\015'))) {
    failed ("Case 14: !isalnum ('\\015')");
  }
  
  /* Case 15 */
  if (!(!isalnum ('\016'))) {
    failed ("Case 15: !isalnum ('\\016')");
  }
  
  /* Case 16 */
  if (!(!isalnum ('\017'))) {
    failed ("Case 16: !isalnum ('\\017')");
  }
  
  /* Case 17 */
  if (!(!isalnum ('\020'))) {
    failed ("Case 17: !isalnum ('\\020')");
  }
  
  /* Case 18 */
  if (!(!isalnum ('\021'))) {
    failed ("Case 18: !isalnum ('\\021')");
  }
  
  /* Case 19 */
  if (!(!isalnum ('\022'))) {
    failed ("Case 19: !isalnum ('\\022')");
  }
  
  /* Case 20 */
  if (!(!isalnum ('\023'))) {
    failed ("Case 20: !isalnum ('\\023')");
  }
  
  /* Case 21 */
  if (!(!isalnum ('\024'))) {
    failed ("Case 21: !isalnum ('\\024')");
  }
  
  /* Case 22 */
  if (!(!isalnum ('\025'))) {
    failed ("Case 22: !isalnum ('\\025')");
  }
  
  /* Case 23 */
  if (!(!isalnum ('\026'))) {
    failed ("Case 23: !isalnum ('\\026')");
  }
  
  /* Case 24 */
  if (!(!isalnum ('\027'))) {
    failed ("Case 24: !isalnum ('\\027')");
  }
  
  /* Case 25 */
  if (!(!isalnum ('\030'))) {
    failed ("Case 25: !isalnum ('\\030')");
  }
  
  /* Case 26 */
  if (!(!isalnum ('\031'))) {
    failed ("Case 26: !isalnum ('\\031')");
  }
  
  /* Case 27 */
  if (!(!isalnum ('\032'))) {
    failed ("Case 27: !isalnum ('\\032')");
  }
  
  /* Case 28 */
  if (!(!isalnum ('\033'))) {
    failed ("Case 28: !isalnum ('\\033')");
  }
  
  /* Case 29 */
  if (!(!isalnum ('\034'))) {
    failed ("Case 29: !isalnum ('\\034')");
  }
  
  /* Case 30 */
  if (!(!isalnum ('\035'))) {
    failed ("Case 30: !isalnum ('\\035')");
  }
  
  /* Case 31 */
  if (!(!isalnum ('\036'))) {
    failed ("Case 31: !isalnum ('\\036')");
  }
  
  /* Case 32 */
  if (!(!isalnum ('\037'))) {
    failed ("Case 32: !isalnum ('\\037')");
  }
  
  /* Case 33 */
  if (!(!isalnum (' '))) {
    failed ("Case 33: !isalnum (' ')");
  }
  
  /* Case 34 */
  if (!(!isalnum ('!'))) {
    failed ("Case 34: !isalnum ('!')");
  }
  
  /* Case 35 */
  if (!(!isalnum ('\"'))) {
    failed ("Case 35: !isalnum ('\\\"')");
  }
  
  /* Case 36 */
  if (!(!isalnum ('#'))) {
    failed ("Case 36: !isalnum ('#')");
  }
  
  /* Case 37 */
  if (!(!isalnum ('$'))) {
    failed ("Case 37: !isalnum ('$')");
  }
  
  /* Case 38 */
  if (!(!isalnum ('%'))) {
    failed ("Case 38: !isalnum ('%')");
  }
  
  /* Case 39 */
  if (!(!isalnum ('&'))) {
    failed ("Case 39: !isalnum ('&')");
  }
  
  /* Case 40 */
  if (!(!isalnum ('\''))) {
    failed ("Case 40: !isalnum ('\\'')");
  }
  
  /* Case 41 */
  if (!(!isalnum ('('))) {
    failed ("Case 41: !isalnum ('(')");
  }
  
  /* Case 42 */
  if (!(!isalnum (')'))) {
    failed ("Case 42: !isalnum (')')");
  }
  
  /* Case 43 */
  if (!(!isalnum ('*'))) {
    failed ("Case 43: !isalnum ('*')");
  }
  
  /* Case 44 */
  if (!(!isalnum ('+'))) {
    failed ("Case 44: !isalnum ('+')");
  }
  
  /* Case 45 */
  if (!(!isalnum (','))) {
    failed ("Case 45: !isalnum (',')");
  }
  
  /* Case 46 */
  if (!(!isalnum ('-'))) {
    failed ("Case 46: !isalnum ('-')");
  }
  
  /* Case 47 */
  if (!(!isalnum ('.'))) {
    failed ("Case 47: !isalnum ('.')");
  }
  
  /* Case 48 */
  if (!(!isalnum ('/'))) {
    failed ("Case 48: !isalnum ('/')");
  }
  
  /* Case 49 */
  if (!(isalnum ('0'))) {
    failed ("Case 49: isalnum ('0')");
  }
  
  /* Case 50 */
  if (!(isalnum ('1'))) {
    failed ("Case 50: isalnum ('1')");
  }
  
  /* Case 51 */
  if (!(isalnum ('2'))) {
    failed ("Case 51: isalnum ('2')");
  }
  
  /* Case 52 */
  if (!(isalnum ('3'))) {
    failed ("Case 52: isalnum ('3')");
  }
  
  /* Case 53 */
  if (!(isalnum ('4'))) {
    failed ("Case 53: isalnum ('4')");
  }
  
  /* Case 54 */
  if (!(isalnum ('5'))) {
    failed ("Case 54: isalnum ('5')");
  }
  
  /* Case 55 */
  if (!(isalnum ('6'))) {
    failed ("Case 55: isalnum ('6')");
  }
  
  /* Case 56 */
  if (!(isalnum ('7'))) {
    failed ("Case 56: isalnum ('7')");
  }
  
  /* Case 57 */
  if (!(isalnum ('8'))) {
    failed ("Case 57: isalnum ('8')");
  }
  
  /* Case 58 */
  if (!(isalnum ('9'))) {
    failed ("Case 58: isalnum ('9')");
  }
  
  /* Case 59 */
  if (!(!isalnum (':'))) {
    failed ("Case 59: !isalnum (':')");
  }
  
  /* Case 60 */
  if (!(!isalnum (';'))) {
    failed ("Case 60: !isalnum (';')");
  }
  
  /* Case 61 */
  if (!(!isalnum ('<'))) {
    failed ("Case 61: !isalnum ('<')");
  }
  
  /* Case 62 */
  if (!(!isalnum ('='))) {
    failed ("Case 62: !isalnum ('=')");
  }
  
  /* Case 63 */
  if (!(!isalnum ('>'))) {
    failed ("Case 63: !isalnum ('>')");
  }
  
  /* Case 64 */
  if (!(!isalnum ('?'))) {
    failed ("Case 64: !isalnum ('?')");
  }
  
  /* Case 65 */
  if (!(!isalnum ('@'))) {
    failed ("Case 65: !isalnum ('@')");
  }
  
  /* Case 66 */
  if (!(isalnum ('A'))) {
    failed ("Case 66: isalnum ('A')");
  }
  
  /* Case 67 */
  if (!(isalnum ('B'))) {
    failed ("Case 67: isalnum ('B')");
  }
  
  /* Case 68 */
  if (!(isalnum ('C'))) {
    failed ("Case 68: isalnum ('C')");
  }
  
  /* Case 69 */
  if (!(isalnum ('D'))) {
    failed ("Case 69: isalnum ('D')");
  }
  
  /* Case 70 */
  if (!(isalnum ('E'))) {
    failed ("Case 70: isalnum ('E')");
  }
  
  /* Case 71 */
  if (!(isalnum ('F'))) {
    failed ("Case 71: isalnum ('F')");
  }
  
  /* Case 72 */
  if (!(isalnum ('G'))) {
    failed ("Case 72: isalnum ('G')");
  }
  
  /* Case 73 */
  if (!(isalnum ('H'))) {
    failed ("Case 73: isalnum ('H')");
  }
  
  /* Case 74 */
  if (!(isalnum ('I'))) {
    failed ("Case 74: isalnum ('I')");
  }
  
  /* Case 75 */
  if (!(isalnum ('J'))) {
    failed ("Case 75: isalnum ('J')");
  }
  
  /* Case 76 */
  if (!(isalnum ('K'))) {
    failed ("Case 76: isalnum ('K')");
  }
  
  /* Case 77 */
  if (!(isalnum ('L'))) {
    failed ("Case 77: isalnum ('L')");
  }
  
  /* Case 78 */
  if (!(isalnum ('M'))) {
    failed ("Case 78: isalnum ('M')");
  }
  
  /* Case 79 */
  if (!(isalnum ('N'))) {
    failed ("Case 79: isalnum ('N')");
  }
  
  /* Case 80 */
  if (!(isalnum ('O'))) {
    failed ("Case 80: isalnum ('O')");
  }
  
  /* Case 81 */
  if (!(isalnum ('P'))) {
    failed ("Case 81: isalnum ('P')");
  }
  
  /* Case 82 */
  if (!(isalnum ('Q'))) {
    failed ("Case 82: isalnum ('Q')");
  }
  
  /* Case 83 */
  if (!(isalnum ('R'))) {
    failed ("Case 83: isalnum ('R')");
  }
  
  /* Case 84 */
  if (!(isalnum ('S'))) {
    failed ("Case 84: isalnum ('S')");
  }
  
  /* Case 85 */
  if (!(isalnum ('T'))) {
    failed ("Case 85: isalnum ('T')");
  }
  
  /* Case 86 */
  if (!(isalnum ('U'))) {
    failed ("Case 86: isalnum ('U')");
  }
  
  /* Case 87 */
  if (!(isalnum ('V'))) {
    failed ("Case 87: isalnum ('V')");
  }
  
  /* Case 88 */
  if (!(isalnum ('W'))) {
    failed ("Case 88: isalnum ('W')");
  }
  
  /* Case 89 */
  if (!(isalnum ('X'))) {
    failed ("Case 89: isalnum ('X')");
  }
  
  /* Case 90 */
  if (!(isalnum ('Y'))) {
    failed ("Case 90: isalnum ('Y')");
  }
  
  /* Case 91 */
  if (!(isalnum ('Z'))) {
    failed ("Case 91: isalnum ('Z')");
  }
  
  /* Case 92 */
  if (!(!isalnum ('['))) {
    failed ("Case 92: !isalnum ('[')");
  }
  
  /* Case 93 */
  if (!(!isalnum ('\\'))) {
    failed ("Case 93: !isalnum ('\\\\')");
  }
  
  /* Case 94 */
  if (!(!isalnum (']'))) {
    failed ("Case 94: !isalnum (']')");
  }
  
  /* Case 95 */
  if (!(!isalnum ('^'))) {
    failed ("Case 95: !isalnum ('^')");
  }
  
  /* Case 96 */
  if (!(!isalnum ('_'))) {
    failed ("Case 96: !isalnum ('_')");
  }
  
  /* Case 97 */
  if (!(!isalnum ('`'))) {
    failed ("Case 97: !isalnum ('`')");
  }
  
  /* Case 98 */
  if (!(isalnum ('a'))) {
    failed ("Case 98: isalnum ('a')");
  }
  
  /* Case 99 */
  if (!(isalnum ('b'))) {
    failed ("Case 99: isalnum ('b')");
  }
  
  /* Case 100 */
  if (!(isalnum ('c'))) {
    failed ("Case 100: isalnum ('c')");
  }
  
  /* Case 101 */
  if (!(isalnum ('d'))) {
    failed ("Case 101: isalnum ('d')");
  }
  
  /* Case 102 */
  if (!(isalnum ('e'))) {
    failed ("Case 102: isalnum ('e')");
  }
  
  /* Case 103 */
  if (!(isalnum ('f'))) {
    failed ("Case 103: isalnum ('f')");
  }
  
  /* Case 104 */
  if (!(isalnum ('g'))) {
    failed ("Case 104: isalnum ('g')");
  }
  
  /* Case 105 */
  if (!(isalnum ('h'))) {
    failed ("Case 105: isalnum ('h')");
  }
  
  /* Case 106 */
  if (!(isalnum ('i'))) {
    failed ("Case 106: isalnum ('i')");
  }
  
  /* Case 107 */
  if (!(isalnum ('j'))) {
    failed ("Case 107: isalnum ('j')");
  }
  
  /* Case 108 */
  if (!(isalnum ('k'))) {
    failed ("Case 108: isalnum ('k')");
  }
  
  /* Case 109 */
  if (!(isalnum ('l'))) {
    failed ("Case 109: isalnum ('l')");
  }
  
  /* Case 110 */
  if (!(isalnum ('m'))) {
    failed ("Case 110: isalnum ('m')");
  }
  
  /* Case 111 */
  if (!(isalnum ('n'))) {
    failed ("Case 111: isalnum ('n')");
  }
  
  /* Case 112 */
  if (!(isalnum ('o'))) {
    failed ("Case 112: isalnum ('o')");
  }
  
  /* Case 113 */
  if (!(isalnum ('p'))) {
    failed ("Case 113: isalnum ('p')");
  }
  
  /* Case 114 */
  if (!(isalnum ('q'))) {
    failed ("Case 114: isalnum ('q')");
  }
  
  /* Case 115 */
  if (!(isalnum ('r'))) {
    failed ("Case 115: isalnum ('r')");
  }
  
  /* Case 116 */
  if (!(isalnum ('s'))) {
    failed ("Case 116: isalnum ('s')");
  }
  
  /* Case 117 */
  if (!(isalnum ('t'))) {
    failed ("Case 117: isalnum ('t')");
  }
  
  /* Case 118 */
  if (!(isalnum ('u'))) {
    failed ("Case 118: isalnum ('u')");
  }
  
  /* Case 119 */
  if (!(isalnum ('v'))) {
    failed ("Case 119: isalnum ('v')");
  }
  
  /* Case 120 */
  if (!(isalnum ('w'))) {
    failed ("Case 120: isalnum ('w')");
  }
  
  /* Case 121 */
  if (!(isalnum ('x'))) {
    failed ("Case 121: isalnum ('x')");
  }
  
  /* Case 122 */
  if (!(isalnum ('y'))) {
    failed ("Case 122: isalnum ('y')");
  }
  
  /* Case 123 */
  if (!(isalnum ('z'))) {
    failed ("Case 123: isalnum ('z')");
  }
  
  /* Case 124 */
  if (!(!isalnum ('{'))) {
    failed ("Case 124: !isalnum ('{')");
  }
  
  /* Case 125 */
  if (!(!isalnum ('|'))) {
    failed ("Case 125: !isalnum ('|')");
  }
  
  /* Case 126 */
  if (!(!isalnum ('}'))) {
    failed ("Case 126: !isalnum ('}')");
  }
  
  /* Case 127 */
  if (!(!isalnum ('~'))) {
    failed ("Case 127: !isalnum ('~')");
  }
  
  /* Case 128 */
  if (!(!isalnum ('\177'))) {
    failed ("Case 128: !isalnum ('\\177')");
  }
  
}


void main ()
{
  test ("test-isalnum", "Test for ANSI Standard C: 7.3.1.1");

  do_test ();

  result ();
}

