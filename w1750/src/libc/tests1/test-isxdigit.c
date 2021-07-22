/*
 * Test for ANSI Standard C: 7.3.1.11
 * 
 * #include <ctype.h>
 * int isxdigit (int c);
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


static char *_test_isxdigit_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(!isxdigit ('\000'))) {
    failed ("Case 1: !isxdigit ('\\000')");
  }
  
  /* Case 2 */
  if (!(!isxdigit ('\001'))) {
    failed ("Case 2: !isxdigit ('\\001')");
  }
  
  /* Case 3 */
  if (!(!isxdigit ('\002'))) {
    failed ("Case 3: !isxdigit ('\\002')");
  }
  
  /* Case 4 */
  if (!(!isxdigit ('\003'))) {
    failed ("Case 4: !isxdigit ('\\003')");
  }
  
  /* Case 5 */
  if (!(!isxdigit ('\004'))) {
    failed ("Case 5: !isxdigit ('\\004')");
  }
  
  /* Case 6 */
  if (!(!isxdigit ('\005'))) {
    failed ("Case 6: !isxdigit ('\\005')");
  }
  
  /* Case 7 */
  if (!(!isxdigit ('\006'))) {
    failed ("Case 7: !isxdigit ('\\006')");
  }
  
  /* Case 8 */
  if (!(!isxdigit ('\007'))) {
    failed ("Case 8: !isxdigit ('\\007')");
  }
  
  /* Case 9 */
  if (!(!isxdigit ('\010'))) {
    failed ("Case 9: !isxdigit ('\\010')");
  }
  
  /* Case 10 */
  if (!(!isxdigit ('\011'))) {
    failed ("Case 10: !isxdigit ('\\011')");
  }
  
  /* Case 11 */
  if (!(!isxdigit ('\012'))) {
    failed ("Case 11: !isxdigit ('\\012')");
  }
  
  /* Case 12 */
  if (!(!isxdigit ('\013'))) {
    failed ("Case 12: !isxdigit ('\\013')");
  }
  
  /* Case 13 */
  if (!(!isxdigit ('\014'))) {
    failed ("Case 13: !isxdigit ('\\014')");
  }
  
  /* Case 14 */
  if (!(!isxdigit ('\015'))) {
    failed ("Case 14: !isxdigit ('\\015')");
  }
  
  /* Case 15 */
  if (!(!isxdigit ('\016'))) {
    failed ("Case 15: !isxdigit ('\\016')");
  }
  
  /* Case 16 */
  if (!(!isxdigit ('\017'))) {
    failed ("Case 16: !isxdigit ('\\017')");
  }
  
  /* Case 17 */
  if (!(!isxdigit ('\020'))) {
    failed ("Case 17: !isxdigit ('\\020')");
  }
  
  /* Case 18 */
  if (!(!isxdigit ('\021'))) {
    failed ("Case 18: !isxdigit ('\\021')");
  }
  
  /* Case 19 */
  if (!(!isxdigit ('\022'))) {
    failed ("Case 19: !isxdigit ('\\022')");
  }
  
  /* Case 20 */
  if (!(!isxdigit ('\023'))) {
    failed ("Case 20: !isxdigit ('\\023')");
  }
  
  /* Case 21 */
  if (!(!isxdigit ('\024'))) {
    failed ("Case 21: !isxdigit ('\\024')");
  }
  
  /* Case 22 */
  if (!(!isxdigit ('\025'))) {
    failed ("Case 22: !isxdigit ('\\025')");
  }
  
  /* Case 23 */
  if (!(!isxdigit ('\026'))) {
    failed ("Case 23: !isxdigit ('\\026')");
  }
  
  /* Case 24 */
  if (!(!isxdigit ('\027'))) {
    failed ("Case 24: !isxdigit ('\\027')");
  }
  
  /* Case 25 */
  if (!(!isxdigit ('\030'))) {
    failed ("Case 25: !isxdigit ('\\030')");
  }
  
  /* Case 26 */
  if (!(!isxdigit ('\031'))) {
    failed ("Case 26: !isxdigit ('\\031')");
  }
  
  /* Case 27 */
  if (!(!isxdigit ('\032'))) {
    failed ("Case 27: !isxdigit ('\\032')");
  }
  
  /* Case 28 */
  if (!(!isxdigit ('\033'))) {
    failed ("Case 28: !isxdigit ('\\033')");
  }
  
  /* Case 29 */
  if (!(!isxdigit ('\034'))) {
    failed ("Case 29: !isxdigit ('\\034')");
  }
  
  /* Case 30 */
  if (!(!isxdigit ('\035'))) {
    failed ("Case 30: !isxdigit ('\\035')");
  }
  
  /* Case 31 */
  if (!(!isxdigit ('\036'))) {
    failed ("Case 31: !isxdigit ('\\036')");
  }
  
  /* Case 32 */
  if (!(!isxdigit ('\037'))) {
    failed ("Case 32: !isxdigit ('\\037')");
  }
  
  /* Case 33 */
  if (!(!isxdigit (' '))) {
    failed ("Case 33: !isxdigit (' ')");
  }
  
  /* Case 34 */
  if (!(!isxdigit ('!'))) {
    failed ("Case 34: !isxdigit ('!')");
  }
  
  /* Case 35 */
  if (!(!isxdigit ('\"'))) {
    failed ("Case 35: !isxdigit ('\\\"')");
  }
  
  /* Case 36 */
  if (!(!isxdigit ('#'))) {
    failed ("Case 36: !isxdigit ('#')");
  }
  
  /* Case 37 */
  if (!(!isxdigit ('$'))) {
    failed ("Case 37: !isxdigit ('$')");
  }
  
  /* Case 38 */
  if (!(!isxdigit ('%'))) {
    failed ("Case 38: !isxdigit ('%')");
  }
  
  /* Case 39 */
  if (!(!isxdigit ('&'))) {
    failed ("Case 39: !isxdigit ('&')");
  }
  
  /* Case 40 */
  if (!(!isxdigit ('\''))) {
    failed ("Case 40: !isxdigit ('\\'')");
  }
  
  /* Case 41 */
  if (!(!isxdigit ('('))) {
    failed ("Case 41: !isxdigit ('(')");
  }
  
  /* Case 42 */
  if (!(!isxdigit (')'))) {
    failed ("Case 42: !isxdigit (')')");
  }
  
  /* Case 43 */
  if (!(!isxdigit ('*'))) {
    failed ("Case 43: !isxdigit ('*')");
  }
  
  /* Case 44 */
  if (!(!isxdigit ('+'))) {
    failed ("Case 44: !isxdigit ('+')");
  }
  
  /* Case 45 */
  if (!(!isxdigit (','))) {
    failed ("Case 45: !isxdigit (',')");
  }
  
  /* Case 46 */
  if (!(!isxdigit ('-'))) {
    failed ("Case 46: !isxdigit ('-')");
  }
  
  /* Case 47 */
  if (!(!isxdigit ('.'))) {
    failed ("Case 47: !isxdigit ('.')");
  }
  
  /* Case 48 */
  if (!(!isxdigit ('/'))) {
    failed ("Case 48: !isxdigit ('/')");
  }
  
  /* Case 49 */
  if (!(isxdigit ('0'))) {
    failed ("Case 49: isxdigit ('0')");
  }
  
  /* Case 50 */
  if (!(isxdigit ('1'))) {
    failed ("Case 50: isxdigit ('1')");
  }
  
  /* Case 51 */
  if (!(isxdigit ('2'))) {
    failed ("Case 51: isxdigit ('2')");
  }
  
  /* Case 52 */
  if (!(isxdigit ('3'))) {
    failed ("Case 52: isxdigit ('3')");
  }
  
  /* Case 53 */
  if (!(isxdigit ('4'))) {
    failed ("Case 53: isxdigit ('4')");
  }
  
  /* Case 54 */
  if (!(isxdigit ('5'))) {
    failed ("Case 54: isxdigit ('5')");
  }
  
  /* Case 55 */
  if (!(isxdigit ('6'))) {
    failed ("Case 55: isxdigit ('6')");
  }
  
  /* Case 56 */
  if (!(isxdigit ('7'))) {
    failed ("Case 56: isxdigit ('7')");
  }
  
  /* Case 57 */
  if (!(isxdigit ('8'))) {
    failed ("Case 57: isxdigit ('8')");
  }
  
  /* Case 58 */
  if (!(isxdigit ('9'))) {
    failed ("Case 58: isxdigit ('9')");
  }
  
  /* Case 59 */
  if (!(!isxdigit (':'))) {
    failed ("Case 59: !isxdigit (':')");
  }
  
  /* Case 60 */
  if (!(!isxdigit (';'))) {
    failed ("Case 60: !isxdigit (';')");
  }
  
  /* Case 61 */
  if (!(!isxdigit ('<'))) {
    failed ("Case 61: !isxdigit ('<')");
  }
  
  /* Case 62 */
  if (!(!isxdigit ('='))) {
    failed ("Case 62: !isxdigit ('=')");
  }
  
  /* Case 63 */
  if (!(!isxdigit ('>'))) {
    failed ("Case 63: !isxdigit ('>')");
  }
  
  /* Case 64 */
  if (!(!isxdigit ('?'))) {
    failed ("Case 64: !isxdigit ('?')");
  }
  
  /* Case 65 */
  if (!(!isxdigit ('@'))) {
    failed ("Case 65: !isxdigit ('@')");
  }
  
  /* Case 66 */
  if (!(isxdigit ('A'))) {
    failed ("Case 66: isxdigit ('A')");
  }
  
  /* Case 67 */
  if (!(isxdigit ('B'))) {
    failed ("Case 67: isxdigit ('B')");
  }
  
  /* Case 68 */
  if (!(isxdigit ('C'))) {
    failed ("Case 68: isxdigit ('C')");
  }
  
  /* Case 69 */
  if (!(isxdigit ('D'))) {
    failed ("Case 69: isxdigit ('D')");
  }
  
  /* Case 70 */
  if (!(isxdigit ('E'))) {
    failed ("Case 70: isxdigit ('E')");
  }
  
  /* Case 71 */
  if (!(isxdigit ('F'))) {
    failed ("Case 71: isxdigit ('F')");
  }
  
  /* Case 72 */
  if (!(!isxdigit ('G'))) {
    failed ("Case 72: !isxdigit ('G')");
  }
  
  /* Case 73 */
  if (!(!isxdigit ('H'))) {
    failed ("Case 73: !isxdigit ('H')");
  }
  
  /* Case 74 */
  if (!(!isxdigit ('I'))) {
    failed ("Case 74: !isxdigit ('I')");
  }
  
  /* Case 75 */
  if (!(!isxdigit ('J'))) {
    failed ("Case 75: !isxdigit ('J')");
  }
  
  /* Case 76 */
  if (!(!isxdigit ('K'))) {
    failed ("Case 76: !isxdigit ('K')");
  }
  
  /* Case 77 */
  if (!(!isxdigit ('L'))) {
    failed ("Case 77: !isxdigit ('L')");
  }
  
  /* Case 78 */
  if (!(!isxdigit ('M'))) {
    failed ("Case 78: !isxdigit ('M')");
  }
  
  /* Case 79 */
  if (!(!isxdigit ('N'))) {
    failed ("Case 79: !isxdigit ('N')");
  }
  
  /* Case 80 */
  if (!(!isxdigit ('O'))) {
    failed ("Case 80: !isxdigit ('O')");
  }
  
  /* Case 81 */
  if (!(!isxdigit ('P'))) {
    failed ("Case 81: !isxdigit ('P')");
  }
  
  /* Case 82 */
  if (!(!isxdigit ('Q'))) {
    failed ("Case 82: !isxdigit ('Q')");
  }
  
  /* Case 83 */
  if (!(!isxdigit ('R'))) {
    failed ("Case 83: !isxdigit ('R')");
  }
  
  /* Case 84 */
  if (!(!isxdigit ('S'))) {
    failed ("Case 84: !isxdigit ('S')");
  }
  
  /* Case 85 */
  if (!(!isxdigit ('T'))) {
    failed ("Case 85: !isxdigit ('T')");
  }
  
  /* Case 86 */
  if (!(!isxdigit ('U'))) {
    failed ("Case 86: !isxdigit ('U')");
  }
  
  /* Case 87 */
  if (!(!isxdigit ('V'))) {
    failed ("Case 87: !isxdigit ('V')");
  }
  
  /* Case 88 */
  if (!(!isxdigit ('W'))) {
    failed ("Case 88: !isxdigit ('W')");
  }
  
  /* Case 89 */
  if (!(!isxdigit ('X'))) {
    failed ("Case 89: !isxdigit ('X')");
  }
  
  /* Case 90 */
  if (!(!isxdigit ('Y'))) {
    failed ("Case 90: !isxdigit ('Y')");
  }
  
  /* Case 91 */
  if (!(!isxdigit ('Z'))) {
    failed ("Case 91: !isxdigit ('Z')");
  }
  
  /* Case 92 */
  if (!(!isxdigit ('['))) {
    failed ("Case 92: !isxdigit ('[')");
  }
  
  /* Case 93 */
  if (!(!isxdigit ('\\'))) {
    failed ("Case 93: !isxdigit ('\\\\')");
  }
  
  /* Case 94 */
  if (!(!isxdigit (']'))) {
    failed ("Case 94: !isxdigit (']')");
  }
  
  /* Case 95 */
  if (!(!isxdigit ('^'))) {
    failed ("Case 95: !isxdigit ('^')");
  }
  
  /* Case 96 */
  if (!(!isxdigit ('_'))) {
    failed ("Case 96: !isxdigit ('_')");
  }
  
  /* Case 97 */
  if (!(!isxdigit ('`'))) {
    failed ("Case 97: !isxdigit ('`')");
  }
  
  /* Case 98 */
  if (!(isxdigit ('a'))) {
    failed ("Case 98: isxdigit ('a')");
  }
  
  /* Case 99 */
  if (!(isxdigit ('b'))) {
    failed ("Case 99: isxdigit ('b')");
  }
  
  /* Case 100 */
  if (!(isxdigit ('c'))) {
    failed ("Case 100: isxdigit ('c')");
  }
  
  /* Case 101 */
  if (!(isxdigit ('d'))) {
    failed ("Case 101: isxdigit ('d')");
  }
  
  /* Case 102 */
  if (!(isxdigit ('e'))) {
    failed ("Case 102: isxdigit ('e')");
  }
  
  /* Case 103 */
  if (!(isxdigit ('f'))) {
    failed ("Case 103: isxdigit ('f')");
  }
  
  /* Case 104 */
  if (!(!isxdigit ('g'))) {
    failed ("Case 104: !isxdigit ('g')");
  }
  
  /* Case 105 */
  if (!(!isxdigit ('h'))) {
    failed ("Case 105: !isxdigit ('h')");
  }
  
  /* Case 106 */
  if (!(!isxdigit ('i'))) {
    failed ("Case 106: !isxdigit ('i')");
  }
  
  /* Case 107 */
  if (!(!isxdigit ('j'))) {
    failed ("Case 107: !isxdigit ('j')");
  }
  
  /* Case 108 */
  if (!(!isxdigit ('k'))) {
    failed ("Case 108: !isxdigit ('k')");
  }
  
  /* Case 109 */
  if (!(!isxdigit ('l'))) {
    failed ("Case 109: !isxdigit ('l')");
  }
  
  /* Case 110 */
  if (!(!isxdigit ('m'))) {
    failed ("Case 110: !isxdigit ('m')");
  }
  
  /* Case 111 */
  if (!(!isxdigit ('n'))) {
    failed ("Case 111: !isxdigit ('n')");
  }
  
  /* Case 112 */
  if (!(!isxdigit ('o'))) {
    failed ("Case 112: !isxdigit ('o')");
  }
  
  /* Case 113 */
  if (!(!isxdigit ('p'))) {
    failed ("Case 113: !isxdigit ('p')");
  }
  
  /* Case 114 */
  if (!(!isxdigit ('q'))) {
    failed ("Case 114: !isxdigit ('q')");
  }
  
  /* Case 115 */
  if (!(!isxdigit ('r'))) {
    failed ("Case 115: !isxdigit ('r')");
  }
  
  /* Case 116 */
  if (!(!isxdigit ('s'))) {
    failed ("Case 116: !isxdigit ('s')");
  }
  
  /* Case 117 */
  if (!(!isxdigit ('t'))) {
    failed ("Case 117: !isxdigit ('t')");
  }
  
  /* Case 118 */
  if (!(!isxdigit ('u'))) {
    failed ("Case 118: !isxdigit ('u')");
  }
  
  /* Case 119 */
  if (!(!isxdigit ('v'))) {
    failed ("Case 119: !isxdigit ('v')");
  }
  
  /* Case 120 */
  if (!(!isxdigit ('w'))) {
    failed ("Case 120: !isxdigit ('w')");
  }
  
  /* Case 121 */
  if (!(!isxdigit ('x'))) {
    failed ("Case 121: !isxdigit ('x')");
  }
  
  /* Case 122 */
  if (!(!isxdigit ('y'))) {
    failed ("Case 122: !isxdigit ('y')");
  }
  
  /* Case 123 */
  if (!(!isxdigit ('z'))) {
    failed ("Case 123: !isxdigit ('z')");
  }
  
  /* Case 124 */
  if (!(!isxdigit ('{'))) {
    failed ("Case 124: !isxdigit ('{')");
  }
  
  /* Case 125 */
  if (!(!isxdigit ('|'))) {
    failed ("Case 125: !isxdigit ('|')");
  }
  
  /* Case 126 */
  if (!(!isxdigit ('}'))) {
    failed ("Case 126: !isxdigit ('}')");
  }
  
  /* Case 127 */
  if (!(!isxdigit ('~'))) {
    failed ("Case 127: !isxdigit ('~')");
  }
  
  /* Case 128 */
  if (!(!isxdigit ('\177'))) {
    failed ("Case 128: !isxdigit ('\\177')");
  }
  
}


void main ()
{
  test ("test-isxdigit", "Test for ANSI Standard C: 7.3.1.11");

  do_test ();

  result ();
}

