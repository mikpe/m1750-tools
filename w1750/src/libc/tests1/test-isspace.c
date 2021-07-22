/*
 * Test for ANSI Standard C: 7.3.1.9
 * 
 * #include <ctype.h>
 * int isspace (int c);
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


static char *_test_isspace_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(!isspace ('\000'))) {
    failed ("Case 1: !isspace ('\\000')");
  }
  
  /* Case 2 */
  if (!(!isspace ('\001'))) {
    failed ("Case 2: !isspace ('\\001')");
  }
  
  /* Case 3 */
  if (!(!isspace ('\002'))) {
    failed ("Case 3: !isspace ('\\002')");
  }
  
  /* Case 4 */
  if (!(!isspace ('\003'))) {
    failed ("Case 4: !isspace ('\\003')");
  }
  
  /* Case 5 */
  if (!(!isspace ('\004'))) {
    failed ("Case 5: !isspace ('\\004')");
  }
  
  /* Case 6 */
  if (!(!isspace ('\005'))) {
    failed ("Case 6: !isspace ('\\005')");
  }
  
  /* Case 7 */
  if (!(!isspace ('\006'))) {
    failed ("Case 7: !isspace ('\\006')");
  }
  
  /* Case 8 */
  if (!(!isspace ('\007'))) {
    failed ("Case 8: !isspace ('\\007')");
  }
  
  /* Case 9 */
  if (!(!isspace ('\010'))) {
    failed ("Case 9: !isspace ('\\010')");
  }
  
  /* Case 10 */
  if (!(isspace ('\011'))) {
    failed ("Case 10: isspace ('\\011')");
  }
  
  /* Case 11 */
  if (!(isspace ('\012'))) {
    failed ("Case 11: isspace ('\\012')");
  }
  
  /* Case 12 */
  if (!(isspace ('\013'))) {
    failed ("Case 12: isspace ('\\013')");
  }
  
  /* Case 13 */
  if (!(isspace ('\014'))) {
    failed ("Case 13: isspace ('\\014')");
  }
  
  /* Case 14 */
  if (!(isspace ('\015'))) {
    failed ("Case 14: isspace ('\\015')");
  }
  
  /* Case 15 */
  if (!(!isspace ('\016'))) {
    failed ("Case 15: !isspace ('\\016')");
  }
  
  /* Case 16 */
  if (!(!isspace ('\017'))) {
    failed ("Case 16: !isspace ('\\017')");
  }
  
  /* Case 17 */
  if (!(!isspace ('\020'))) {
    failed ("Case 17: !isspace ('\\020')");
  }
  
  /* Case 18 */
  if (!(!isspace ('\021'))) {
    failed ("Case 18: !isspace ('\\021')");
  }
  
  /* Case 19 */
  if (!(!isspace ('\022'))) {
    failed ("Case 19: !isspace ('\\022')");
  }
  
  /* Case 20 */
  if (!(!isspace ('\023'))) {
    failed ("Case 20: !isspace ('\\023')");
  }
  
  /* Case 21 */
  if (!(!isspace ('\024'))) {
    failed ("Case 21: !isspace ('\\024')");
  }
  
  /* Case 22 */
  if (!(!isspace ('\025'))) {
    failed ("Case 22: !isspace ('\\025')");
  }
  
  /* Case 23 */
  if (!(!isspace ('\026'))) {
    failed ("Case 23: !isspace ('\\026')");
  }
  
  /* Case 24 */
  if (!(!isspace ('\027'))) {
    failed ("Case 24: !isspace ('\\027')");
  }
  
  /* Case 25 */
  if (!(!isspace ('\030'))) {
    failed ("Case 25: !isspace ('\\030')");
  }
  
  /* Case 26 */
  if (!(!isspace ('\031'))) {
    failed ("Case 26: !isspace ('\\031')");
  }
  
  /* Case 27 */
  if (!(!isspace ('\032'))) {
    failed ("Case 27: !isspace ('\\032')");
  }
  
  /* Case 28 */
  if (!(!isspace ('\033'))) {
    failed ("Case 28: !isspace ('\\033')");
  }
  
  /* Case 29 */
  if (!(!isspace ('\034'))) {
    failed ("Case 29: !isspace ('\\034')");
  }
  
  /* Case 30 */
  if (!(!isspace ('\035'))) {
    failed ("Case 30: !isspace ('\\035')");
  }
  
  /* Case 31 */
  if (!(!isspace ('\036'))) {
    failed ("Case 31: !isspace ('\\036')");
  }
  
  /* Case 32 */
  if (!(!isspace ('\037'))) {
    failed ("Case 32: !isspace ('\\037')");
  }
  
  /* Case 33 */
  if (!(isspace (' '))) {
    failed ("Case 33: isspace (' ')");
  }
  
  /* Case 34 */
  if (!(!isspace ('!'))) {
    failed ("Case 34: !isspace ('!')");
  }
  
  /* Case 35 */
  if (!(!isspace ('\"'))) {
    failed ("Case 35: !isspace ('\\\"')");
  }
  
  /* Case 36 */
  if (!(!isspace ('#'))) {
    failed ("Case 36: !isspace ('#')");
  }
  
  /* Case 37 */
  if (!(!isspace ('$'))) {
    failed ("Case 37: !isspace ('$')");
  }
  
  /* Case 38 */
  if (!(!isspace ('%'))) {
    failed ("Case 38: !isspace ('%')");
  }
  
  /* Case 39 */
  if (!(!isspace ('&'))) {
    failed ("Case 39: !isspace ('&')");
  }
  
  /* Case 40 */
  if (!(!isspace ('\''))) {
    failed ("Case 40: !isspace ('\\'')");
  }
  
  /* Case 41 */
  if (!(!isspace ('('))) {
    failed ("Case 41: !isspace ('(')");
  }
  
  /* Case 42 */
  if (!(!isspace (')'))) {
    failed ("Case 42: !isspace (')')");
  }
  
  /* Case 43 */
  if (!(!isspace ('*'))) {
    failed ("Case 43: !isspace ('*')");
  }
  
  /* Case 44 */
  if (!(!isspace ('+'))) {
    failed ("Case 44: !isspace ('+')");
  }
  
  /* Case 45 */
  if (!(!isspace (','))) {
    failed ("Case 45: !isspace (',')");
  }
  
  /* Case 46 */
  if (!(!isspace ('-'))) {
    failed ("Case 46: !isspace ('-')");
  }
  
  /* Case 47 */
  if (!(!isspace ('.'))) {
    failed ("Case 47: !isspace ('.')");
  }
  
  /* Case 48 */
  if (!(!isspace ('/'))) {
    failed ("Case 48: !isspace ('/')");
  }
  
  /* Case 49 */
  if (!(!isspace ('0'))) {
    failed ("Case 49: !isspace ('0')");
  }
  
  /* Case 50 */
  if (!(!isspace ('1'))) {
    failed ("Case 50: !isspace ('1')");
  }
  
  /* Case 51 */
  if (!(!isspace ('2'))) {
    failed ("Case 51: !isspace ('2')");
  }
  
  /* Case 52 */
  if (!(!isspace ('3'))) {
    failed ("Case 52: !isspace ('3')");
  }
  
  /* Case 53 */
  if (!(!isspace ('4'))) {
    failed ("Case 53: !isspace ('4')");
  }
  
  /* Case 54 */
  if (!(!isspace ('5'))) {
    failed ("Case 54: !isspace ('5')");
  }
  
  /* Case 55 */
  if (!(!isspace ('6'))) {
    failed ("Case 55: !isspace ('6')");
  }
  
  /* Case 56 */
  if (!(!isspace ('7'))) {
    failed ("Case 56: !isspace ('7')");
  }
  
  /* Case 57 */
  if (!(!isspace ('8'))) {
    failed ("Case 57: !isspace ('8')");
  }
  
  /* Case 58 */
  if (!(!isspace ('9'))) {
    failed ("Case 58: !isspace ('9')");
  }
  
  /* Case 59 */
  if (!(!isspace (':'))) {
    failed ("Case 59: !isspace (':')");
  }
  
  /* Case 60 */
  if (!(!isspace (';'))) {
    failed ("Case 60: !isspace (';')");
  }
  
  /* Case 61 */
  if (!(!isspace ('<'))) {
    failed ("Case 61: !isspace ('<')");
  }
  
  /* Case 62 */
  if (!(!isspace ('='))) {
    failed ("Case 62: !isspace ('=')");
  }
  
  /* Case 63 */
  if (!(!isspace ('>'))) {
    failed ("Case 63: !isspace ('>')");
  }
  
  /* Case 64 */
  if (!(!isspace ('?'))) {
    failed ("Case 64: !isspace ('?')");
  }
  
  /* Case 65 */
  if (!(!isspace ('@'))) {
    failed ("Case 65: !isspace ('@')");
  }
  
  /* Case 66 */
  if (!(!isspace ('A'))) {
    failed ("Case 66: !isspace ('A')");
  }
  
  /* Case 67 */
  if (!(!isspace ('B'))) {
    failed ("Case 67: !isspace ('B')");
  }
  
  /* Case 68 */
  if (!(!isspace ('C'))) {
    failed ("Case 68: !isspace ('C')");
  }
  
  /* Case 69 */
  if (!(!isspace ('D'))) {
    failed ("Case 69: !isspace ('D')");
  }
  
  /* Case 70 */
  if (!(!isspace ('E'))) {
    failed ("Case 70: !isspace ('E')");
  }
  
  /* Case 71 */
  if (!(!isspace ('F'))) {
    failed ("Case 71: !isspace ('F')");
  }
  
  /* Case 72 */
  if (!(!isspace ('G'))) {
    failed ("Case 72: !isspace ('G')");
  }
  
  /* Case 73 */
  if (!(!isspace ('H'))) {
    failed ("Case 73: !isspace ('H')");
  }
  
  /* Case 74 */
  if (!(!isspace ('I'))) {
    failed ("Case 74: !isspace ('I')");
  }
  
  /* Case 75 */
  if (!(!isspace ('J'))) {
    failed ("Case 75: !isspace ('J')");
  }
  
  /* Case 76 */
  if (!(!isspace ('K'))) {
    failed ("Case 76: !isspace ('K')");
  }
  
  /* Case 77 */
  if (!(!isspace ('L'))) {
    failed ("Case 77: !isspace ('L')");
  }
  
  /* Case 78 */
  if (!(!isspace ('M'))) {
    failed ("Case 78: !isspace ('M')");
  }
  
  /* Case 79 */
  if (!(!isspace ('N'))) {
    failed ("Case 79: !isspace ('N')");
  }
  
  /* Case 80 */
  if (!(!isspace ('O'))) {
    failed ("Case 80: !isspace ('O')");
  }
  
  /* Case 81 */
  if (!(!isspace ('P'))) {
    failed ("Case 81: !isspace ('P')");
  }
  
  /* Case 82 */
  if (!(!isspace ('Q'))) {
    failed ("Case 82: !isspace ('Q')");
  }
  
  /* Case 83 */
  if (!(!isspace ('R'))) {
    failed ("Case 83: !isspace ('R')");
  }
  
  /* Case 84 */
  if (!(!isspace ('S'))) {
    failed ("Case 84: !isspace ('S')");
  }
  
  /* Case 85 */
  if (!(!isspace ('T'))) {
    failed ("Case 85: !isspace ('T')");
  }
  
  /* Case 86 */
  if (!(!isspace ('U'))) {
    failed ("Case 86: !isspace ('U')");
  }
  
  /* Case 87 */
  if (!(!isspace ('V'))) {
    failed ("Case 87: !isspace ('V')");
  }
  
  /* Case 88 */
  if (!(!isspace ('W'))) {
    failed ("Case 88: !isspace ('W')");
  }
  
  /* Case 89 */
  if (!(!isspace ('X'))) {
    failed ("Case 89: !isspace ('X')");
  }
  
  /* Case 90 */
  if (!(!isspace ('Y'))) {
    failed ("Case 90: !isspace ('Y')");
  }
  
  /* Case 91 */
  if (!(!isspace ('Z'))) {
    failed ("Case 91: !isspace ('Z')");
  }
  
  /* Case 92 */
  if (!(!isspace ('['))) {
    failed ("Case 92: !isspace ('[')");
  }
  
  /* Case 93 */
  if (!(!isspace ('\\'))) {
    failed ("Case 93: !isspace ('\\\\')");
  }
  
  /* Case 94 */
  if (!(!isspace (']'))) {
    failed ("Case 94: !isspace (']')");
  }
  
  /* Case 95 */
  if (!(!isspace ('^'))) {
    failed ("Case 95: !isspace ('^')");
  }
  
  /* Case 96 */
  if (!(!isspace ('_'))) {
    failed ("Case 96: !isspace ('_')");
  }
  
  /* Case 97 */
  if (!(!isspace ('`'))) {
    failed ("Case 97: !isspace ('`')");
  }
  
  /* Case 98 */
  if (!(!isspace ('a'))) {
    failed ("Case 98: !isspace ('a')");
  }
  
  /* Case 99 */
  if (!(!isspace ('b'))) {
    failed ("Case 99: !isspace ('b')");
  }
  
  /* Case 100 */
  if (!(!isspace ('c'))) {
    failed ("Case 100: !isspace ('c')");
  }
  
  /* Case 101 */
  if (!(!isspace ('d'))) {
    failed ("Case 101: !isspace ('d')");
  }
  
  /* Case 102 */
  if (!(!isspace ('e'))) {
    failed ("Case 102: !isspace ('e')");
  }
  
  /* Case 103 */
  if (!(!isspace ('f'))) {
    failed ("Case 103: !isspace ('f')");
  }
  
  /* Case 104 */
  if (!(!isspace ('g'))) {
    failed ("Case 104: !isspace ('g')");
  }
  
  /* Case 105 */
  if (!(!isspace ('h'))) {
    failed ("Case 105: !isspace ('h')");
  }
  
  /* Case 106 */
  if (!(!isspace ('i'))) {
    failed ("Case 106: !isspace ('i')");
  }
  
  /* Case 107 */
  if (!(!isspace ('j'))) {
    failed ("Case 107: !isspace ('j')");
  }
  
  /* Case 108 */
  if (!(!isspace ('k'))) {
    failed ("Case 108: !isspace ('k')");
  }
  
  /* Case 109 */
  if (!(!isspace ('l'))) {
    failed ("Case 109: !isspace ('l')");
  }
  
  /* Case 110 */
  if (!(!isspace ('m'))) {
    failed ("Case 110: !isspace ('m')");
  }
  
  /* Case 111 */
  if (!(!isspace ('n'))) {
    failed ("Case 111: !isspace ('n')");
  }
  
  /* Case 112 */
  if (!(!isspace ('o'))) {
    failed ("Case 112: !isspace ('o')");
  }
  
  /* Case 113 */
  if (!(!isspace ('p'))) {
    failed ("Case 113: !isspace ('p')");
  }
  
  /* Case 114 */
  if (!(!isspace ('q'))) {
    failed ("Case 114: !isspace ('q')");
  }
  
  /* Case 115 */
  if (!(!isspace ('r'))) {
    failed ("Case 115: !isspace ('r')");
  }
  
  /* Case 116 */
  if (!(!isspace ('s'))) {
    failed ("Case 116: !isspace ('s')");
  }
  
  /* Case 117 */
  if (!(!isspace ('t'))) {
    failed ("Case 117: !isspace ('t')");
  }
  
  /* Case 118 */
  if (!(!isspace ('u'))) {
    failed ("Case 118: !isspace ('u')");
  }
  
  /* Case 119 */
  if (!(!isspace ('v'))) {
    failed ("Case 119: !isspace ('v')");
  }
  
  /* Case 120 */
  if (!(!isspace ('w'))) {
    failed ("Case 120: !isspace ('w')");
  }
  
  /* Case 121 */
  if (!(!isspace ('x'))) {
    failed ("Case 121: !isspace ('x')");
  }
  
  /* Case 122 */
  if (!(!isspace ('y'))) {
    failed ("Case 122: !isspace ('y')");
  }
  
  /* Case 123 */
  if (!(!isspace ('z'))) {
    failed ("Case 123: !isspace ('z')");
  }
  
  /* Case 124 */
  if (!(!isspace ('{'))) {
    failed ("Case 124: !isspace ('{')");
  }
  
  /* Case 125 */
  if (!(!isspace ('|'))) {
    failed ("Case 125: !isspace ('|')");
  }
  
  /* Case 126 */
  if (!(!isspace ('}'))) {
    failed ("Case 126: !isspace ('}')");
  }
  
  /* Case 127 */
  if (!(!isspace ('~'))) {
    failed ("Case 127: !isspace ('~')");
  }
  
  /* Case 128 */
  if (!(!isspace ('\177'))) {
    failed ("Case 128: !isspace ('\\177')");
  }
  
}


void main ()
{
  test ("test-isspace", "Test for ANSI Standard C: 7.3.1.9");

  do_test ();

  result ();
}

