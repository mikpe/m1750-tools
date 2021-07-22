/*
 * Test for ANSI Standard C: 7.3.1.4
 * 
 * #include <ctype.h>
 * int isdigit (int c);
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


static char *_test_isdigit_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(!isdigit ('\000'))) {
    failed ("Case 1: !isdigit ('\\000')");
  }
  
  /* Case 2 */
  if (!(!isdigit ('\001'))) {
    failed ("Case 2: !isdigit ('\\001')");
  }
  
  /* Case 3 */
  if (!(!isdigit ('\002'))) {
    failed ("Case 3: !isdigit ('\\002')");
  }
  
  /* Case 4 */
  if (!(!isdigit ('\003'))) {
    failed ("Case 4: !isdigit ('\\003')");
  }
  
  /* Case 5 */
  if (!(!isdigit ('\004'))) {
    failed ("Case 5: !isdigit ('\\004')");
  }
  
  /* Case 6 */
  if (!(!isdigit ('\005'))) {
    failed ("Case 6: !isdigit ('\\005')");
  }
  
  /* Case 7 */
  if (!(!isdigit ('\006'))) {
    failed ("Case 7: !isdigit ('\\006')");
  }
  
  /* Case 8 */
  if (!(!isdigit ('\007'))) {
    failed ("Case 8: !isdigit ('\\007')");
  }
  
  /* Case 9 */
  if (!(!isdigit ('\010'))) {
    failed ("Case 9: !isdigit ('\\010')");
  }
  
  /* Case 10 */
  if (!(!isdigit ('\011'))) {
    failed ("Case 10: !isdigit ('\\011')");
  }
  
  /* Case 11 */
  if (!(!isdigit ('\012'))) {
    failed ("Case 11: !isdigit ('\\012')");
  }
  
  /* Case 12 */
  if (!(!isdigit ('\013'))) {
    failed ("Case 12: !isdigit ('\\013')");
  }
  
  /* Case 13 */
  if (!(!isdigit ('\014'))) {
    failed ("Case 13: !isdigit ('\\014')");
  }
  
  /* Case 14 */
  if (!(!isdigit ('\015'))) {
    failed ("Case 14: !isdigit ('\\015')");
  }
  
  /* Case 15 */
  if (!(!isdigit ('\016'))) {
    failed ("Case 15: !isdigit ('\\016')");
  }
  
  /* Case 16 */
  if (!(!isdigit ('\017'))) {
    failed ("Case 16: !isdigit ('\\017')");
  }
  
  /* Case 17 */
  if (!(!isdigit ('\020'))) {
    failed ("Case 17: !isdigit ('\\020')");
  }
  
  /* Case 18 */
  if (!(!isdigit ('\021'))) {
    failed ("Case 18: !isdigit ('\\021')");
  }
  
  /* Case 19 */
  if (!(!isdigit ('\022'))) {
    failed ("Case 19: !isdigit ('\\022')");
  }
  
  /* Case 20 */
  if (!(!isdigit ('\023'))) {
    failed ("Case 20: !isdigit ('\\023')");
  }
  
  /* Case 21 */
  if (!(!isdigit ('\024'))) {
    failed ("Case 21: !isdigit ('\\024')");
  }
  
  /* Case 22 */
  if (!(!isdigit ('\025'))) {
    failed ("Case 22: !isdigit ('\\025')");
  }
  
  /* Case 23 */
  if (!(!isdigit ('\026'))) {
    failed ("Case 23: !isdigit ('\\026')");
  }
  
  /* Case 24 */
  if (!(!isdigit ('\027'))) {
    failed ("Case 24: !isdigit ('\\027')");
  }
  
  /* Case 25 */
  if (!(!isdigit ('\030'))) {
    failed ("Case 25: !isdigit ('\\030')");
  }
  
  /* Case 26 */
  if (!(!isdigit ('\031'))) {
    failed ("Case 26: !isdigit ('\\031')");
  }
  
  /* Case 27 */
  if (!(!isdigit ('\032'))) {
    failed ("Case 27: !isdigit ('\\032')");
  }
  
  /* Case 28 */
  if (!(!isdigit ('\033'))) {
    failed ("Case 28: !isdigit ('\\033')");
  }
  
  /* Case 29 */
  if (!(!isdigit ('\034'))) {
    failed ("Case 29: !isdigit ('\\034')");
  }
  
  /* Case 30 */
  if (!(!isdigit ('\035'))) {
    failed ("Case 30: !isdigit ('\\035')");
  }
  
  /* Case 31 */
  if (!(!isdigit ('\036'))) {
    failed ("Case 31: !isdigit ('\\036')");
  }
  
  /* Case 32 */
  if (!(!isdigit ('\037'))) {
    failed ("Case 32: !isdigit ('\\037')");
  }
  
  /* Case 33 */
  if (!(!isdigit (' '))) {
    failed ("Case 33: !isdigit (' ')");
  }
  
  /* Case 34 */
  if (!(!isdigit ('!'))) {
    failed ("Case 34: !isdigit ('!')");
  }
  
  /* Case 35 */
  if (!(!isdigit ('\"'))) {
    failed ("Case 35: !isdigit ('\\\"')");
  }
  
  /* Case 36 */
  if (!(!isdigit ('#'))) {
    failed ("Case 36: !isdigit ('#')");
  }
  
  /* Case 37 */
  if (!(!isdigit ('$'))) {
    failed ("Case 37: !isdigit ('$')");
  }
  
  /* Case 38 */
  if (!(!isdigit ('%'))) {
    failed ("Case 38: !isdigit ('%')");
  }
  
  /* Case 39 */
  if (!(!isdigit ('&'))) {
    failed ("Case 39: !isdigit ('&')");
  }
  
  /* Case 40 */
  if (!(!isdigit ('\''))) {
    failed ("Case 40: !isdigit ('\\'')");
  }
  
  /* Case 41 */
  if (!(!isdigit ('('))) {
    failed ("Case 41: !isdigit ('(')");
  }
  
  /* Case 42 */
  if (!(!isdigit (')'))) {
    failed ("Case 42: !isdigit (')')");
  }
  
  /* Case 43 */
  if (!(!isdigit ('*'))) {
    failed ("Case 43: !isdigit ('*')");
  }
  
  /* Case 44 */
  if (!(!isdigit ('+'))) {
    failed ("Case 44: !isdigit ('+')");
  }
  
  /* Case 45 */
  if (!(!isdigit (','))) {
    failed ("Case 45: !isdigit (',')");
  }
  
  /* Case 46 */
  if (!(!isdigit ('-'))) {
    failed ("Case 46: !isdigit ('-')");
  }
  
  /* Case 47 */
  if (!(!isdigit ('.'))) {
    failed ("Case 47: !isdigit ('.')");
  }
  
  /* Case 48 */
  if (!(!isdigit ('/'))) {
    failed ("Case 48: !isdigit ('/')");
  }
  
  /* Case 49 */
  if (!(isdigit ('0'))) {
    failed ("Case 49: isdigit ('0')");
  }
  
  /* Case 50 */
  if (!(isdigit ('1'))) {
    failed ("Case 50: isdigit ('1')");
  }
  
  /* Case 51 */
  if (!(isdigit ('2'))) {
    failed ("Case 51: isdigit ('2')");
  }
  
  /* Case 52 */
  if (!(isdigit ('3'))) {
    failed ("Case 52: isdigit ('3')");
  }
  
  /* Case 53 */
  if (!(isdigit ('4'))) {
    failed ("Case 53: isdigit ('4')");
  }
  
  /* Case 54 */
  if (!(isdigit ('5'))) {
    failed ("Case 54: isdigit ('5')");
  }
  
  /* Case 55 */
  if (!(isdigit ('6'))) {
    failed ("Case 55: isdigit ('6')");
  }
  
  /* Case 56 */
  if (!(isdigit ('7'))) {
    failed ("Case 56: isdigit ('7')");
  }
  
  /* Case 57 */
  if (!(isdigit ('8'))) {
    failed ("Case 57: isdigit ('8')");
  }
  
  /* Case 58 */
  if (!(isdigit ('9'))) {
    failed ("Case 58: isdigit ('9')");
  }
  
  /* Case 59 */
  if (!(!isdigit (':'))) {
    failed ("Case 59: !isdigit (':')");
  }
  
  /* Case 60 */
  if (!(!isdigit (';'))) {
    failed ("Case 60: !isdigit (';')");
  }
  
  /* Case 61 */
  if (!(!isdigit ('<'))) {
    failed ("Case 61: !isdigit ('<')");
  }
  
  /* Case 62 */
  if (!(!isdigit ('='))) {
    failed ("Case 62: !isdigit ('=')");
  }
  
  /* Case 63 */
  if (!(!isdigit ('>'))) {
    failed ("Case 63: !isdigit ('>')");
  }
  
  /* Case 64 */
  if (!(!isdigit ('?'))) {
    failed ("Case 64: !isdigit ('?')");
  }
  
  /* Case 65 */
  if (!(!isdigit ('@'))) {
    failed ("Case 65: !isdigit ('@')");
  }
  
  /* Case 66 */
  if (!(!isdigit ('A'))) {
    failed ("Case 66: !isdigit ('A')");
  }
  
  /* Case 67 */
  if (!(!isdigit ('B'))) {
    failed ("Case 67: !isdigit ('B')");
  }
  
  /* Case 68 */
  if (!(!isdigit ('C'))) {
    failed ("Case 68: !isdigit ('C')");
  }
  
  /* Case 69 */
  if (!(!isdigit ('D'))) {
    failed ("Case 69: !isdigit ('D')");
  }
  
  /* Case 70 */
  if (!(!isdigit ('E'))) {
    failed ("Case 70: !isdigit ('E')");
  }
  
  /* Case 71 */
  if (!(!isdigit ('F'))) {
    failed ("Case 71: !isdigit ('F')");
  }
  
  /* Case 72 */
  if (!(!isdigit ('G'))) {
    failed ("Case 72: !isdigit ('G')");
  }
  
  /* Case 73 */
  if (!(!isdigit ('H'))) {
    failed ("Case 73: !isdigit ('H')");
  }
  
  /* Case 74 */
  if (!(!isdigit ('I'))) {
    failed ("Case 74: !isdigit ('I')");
  }
  
  /* Case 75 */
  if (!(!isdigit ('J'))) {
    failed ("Case 75: !isdigit ('J')");
  }
  
  /* Case 76 */
  if (!(!isdigit ('K'))) {
    failed ("Case 76: !isdigit ('K')");
  }
  
  /* Case 77 */
  if (!(!isdigit ('L'))) {
    failed ("Case 77: !isdigit ('L')");
  }
  
  /* Case 78 */
  if (!(!isdigit ('M'))) {
    failed ("Case 78: !isdigit ('M')");
  }
  
  /* Case 79 */
  if (!(!isdigit ('N'))) {
    failed ("Case 79: !isdigit ('N')");
  }
  
  /* Case 80 */
  if (!(!isdigit ('O'))) {
    failed ("Case 80: !isdigit ('O')");
  }
  
  /* Case 81 */
  if (!(!isdigit ('P'))) {
    failed ("Case 81: !isdigit ('P')");
  }
  
  /* Case 82 */
  if (!(!isdigit ('Q'))) {
    failed ("Case 82: !isdigit ('Q')");
  }
  
  /* Case 83 */
  if (!(!isdigit ('R'))) {
    failed ("Case 83: !isdigit ('R')");
  }
  
  /* Case 84 */
  if (!(!isdigit ('S'))) {
    failed ("Case 84: !isdigit ('S')");
  }
  
  /* Case 85 */
  if (!(!isdigit ('T'))) {
    failed ("Case 85: !isdigit ('T')");
  }
  
  /* Case 86 */
  if (!(!isdigit ('U'))) {
    failed ("Case 86: !isdigit ('U')");
  }
  
  /* Case 87 */
  if (!(!isdigit ('V'))) {
    failed ("Case 87: !isdigit ('V')");
  }
  
  /* Case 88 */
  if (!(!isdigit ('W'))) {
    failed ("Case 88: !isdigit ('W')");
  }
  
  /* Case 89 */
  if (!(!isdigit ('X'))) {
    failed ("Case 89: !isdigit ('X')");
  }
  
  /* Case 90 */
  if (!(!isdigit ('Y'))) {
    failed ("Case 90: !isdigit ('Y')");
  }
  
  /* Case 91 */
  if (!(!isdigit ('Z'))) {
    failed ("Case 91: !isdigit ('Z')");
  }
  
  /* Case 92 */
  if (!(!isdigit ('['))) {
    failed ("Case 92: !isdigit ('[')");
  }
  
  /* Case 93 */
  if (!(!isdigit ('\\'))) {
    failed ("Case 93: !isdigit ('\\\\')");
  }
  
  /* Case 94 */
  if (!(!isdigit (']'))) {
    failed ("Case 94: !isdigit (']')");
  }
  
  /* Case 95 */
  if (!(!isdigit ('^'))) {
    failed ("Case 95: !isdigit ('^')");
  }
  
  /* Case 96 */
  if (!(!isdigit ('_'))) {
    failed ("Case 96: !isdigit ('_')");
  }
  
  /* Case 97 */
  if (!(!isdigit ('`'))) {
    failed ("Case 97: !isdigit ('`')");
  }
  
  /* Case 98 */
  if (!(!isdigit ('a'))) {
    failed ("Case 98: !isdigit ('a')");
  }
  
  /* Case 99 */
  if (!(!isdigit ('b'))) {
    failed ("Case 99: !isdigit ('b')");
  }
  
  /* Case 100 */
  if (!(!isdigit ('c'))) {
    failed ("Case 100: !isdigit ('c')");
  }
  
  /* Case 101 */
  if (!(!isdigit ('d'))) {
    failed ("Case 101: !isdigit ('d')");
  }
  
  /* Case 102 */
  if (!(!isdigit ('e'))) {
    failed ("Case 102: !isdigit ('e')");
  }
  
  /* Case 103 */
  if (!(!isdigit ('f'))) {
    failed ("Case 103: !isdigit ('f')");
  }
  
  /* Case 104 */
  if (!(!isdigit ('g'))) {
    failed ("Case 104: !isdigit ('g')");
  }
  
  /* Case 105 */
  if (!(!isdigit ('h'))) {
    failed ("Case 105: !isdigit ('h')");
  }
  
  /* Case 106 */
  if (!(!isdigit ('i'))) {
    failed ("Case 106: !isdigit ('i')");
  }
  
  /* Case 107 */
  if (!(!isdigit ('j'))) {
    failed ("Case 107: !isdigit ('j')");
  }
  
  /* Case 108 */
  if (!(!isdigit ('k'))) {
    failed ("Case 108: !isdigit ('k')");
  }
  
  /* Case 109 */
  if (!(!isdigit ('l'))) {
    failed ("Case 109: !isdigit ('l')");
  }
  
  /* Case 110 */
  if (!(!isdigit ('m'))) {
    failed ("Case 110: !isdigit ('m')");
  }
  
  /* Case 111 */
  if (!(!isdigit ('n'))) {
    failed ("Case 111: !isdigit ('n')");
  }
  
  /* Case 112 */
  if (!(!isdigit ('o'))) {
    failed ("Case 112: !isdigit ('o')");
  }
  
  /* Case 113 */
  if (!(!isdigit ('p'))) {
    failed ("Case 113: !isdigit ('p')");
  }
  
  /* Case 114 */
  if (!(!isdigit ('q'))) {
    failed ("Case 114: !isdigit ('q')");
  }
  
  /* Case 115 */
  if (!(!isdigit ('r'))) {
    failed ("Case 115: !isdigit ('r')");
  }
  
  /* Case 116 */
  if (!(!isdigit ('s'))) {
    failed ("Case 116: !isdigit ('s')");
  }
  
  /* Case 117 */
  if (!(!isdigit ('t'))) {
    failed ("Case 117: !isdigit ('t')");
  }
  
  /* Case 118 */
  if (!(!isdigit ('u'))) {
    failed ("Case 118: !isdigit ('u')");
  }
  
  /* Case 119 */
  if (!(!isdigit ('v'))) {
    failed ("Case 119: !isdigit ('v')");
  }
  
  /* Case 120 */
  if (!(!isdigit ('w'))) {
    failed ("Case 120: !isdigit ('w')");
  }
  
  /* Case 121 */
  if (!(!isdigit ('x'))) {
    failed ("Case 121: !isdigit ('x')");
  }
  
  /* Case 122 */
  if (!(!isdigit ('y'))) {
    failed ("Case 122: !isdigit ('y')");
  }
  
  /* Case 123 */
  if (!(!isdigit ('z'))) {
    failed ("Case 123: !isdigit ('z')");
  }
  
  /* Case 124 */
  if (!(!isdigit ('{'))) {
    failed ("Case 124: !isdigit ('{')");
  }
  
  /* Case 125 */
  if (!(!isdigit ('|'))) {
    failed ("Case 125: !isdigit ('|')");
  }
  
  /* Case 126 */
  if (!(!isdigit ('}'))) {
    failed ("Case 126: !isdigit ('}')");
  }
  
  /* Case 127 */
  if (!(!isdigit ('~'))) {
    failed ("Case 127: !isdigit ('~')");
  }
  
  /* Case 128 */
  if (!(!isdigit ('\177'))) {
    failed ("Case 128: !isdigit ('\\177')");
  }
  
}


void main ()
{
  test ("test-isdigit", "Test for ANSI Standard C: 7.3.1.4");

  do_test ();

  result ();
}

