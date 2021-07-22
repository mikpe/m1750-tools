/*
 * Test for ANSI Standard C: 7.3.1.2
 * 
 * #include <ctype.h>
 * int isalpha (int c);
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


static char *_test_isalpha_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(!isalpha ('\000'))) {
    failed ("Case 1: !isalpha ('\\000')");
  }
  
  /* Case 2 */
  if (!(!isalpha ('\001'))) {
    failed ("Case 2: !isalpha ('\\001')");
  }
  
  /* Case 3 */
  if (!(!isalpha ('\002'))) {
    failed ("Case 3: !isalpha ('\\002')");
  }
  
  /* Case 4 */
  if (!(!isalpha ('\003'))) {
    failed ("Case 4: !isalpha ('\\003')");
  }
  
  /* Case 5 */
  if (!(!isalpha ('\004'))) {
    failed ("Case 5: !isalpha ('\\004')");
  }
  
  /* Case 6 */
  if (!(!isalpha ('\005'))) {
    failed ("Case 6: !isalpha ('\\005')");
  }
  
  /* Case 7 */
  if (!(!isalpha ('\006'))) {
    failed ("Case 7: !isalpha ('\\006')");
  }
  
  /* Case 8 */
  if (!(!isalpha ('\007'))) {
    failed ("Case 8: !isalpha ('\\007')");
  }
  
  /* Case 9 */
  if (!(!isalpha ('\010'))) {
    failed ("Case 9: !isalpha ('\\010')");
  }
  
  /* Case 10 */
  if (!(!isalpha ('\011'))) {
    failed ("Case 10: !isalpha ('\\011')");
  }
  
  /* Case 11 */
  if (!(!isalpha ('\012'))) {
    failed ("Case 11: !isalpha ('\\012')");
  }
  
  /* Case 12 */
  if (!(!isalpha ('\013'))) {
    failed ("Case 12: !isalpha ('\\013')");
  }
  
  /* Case 13 */
  if (!(!isalpha ('\014'))) {
    failed ("Case 13: !isalpha ('\\014')");
  }
  
  /* Case 14 */
  if (!(!isalpha ('\015'))) {
    failed ("Case 14: !isalpha ('\\015')");
  }
  
  /* Case 15 */
  if (!(!isalpha ('\016'))) {
    failed ("Case 15: !isalpha ('\\016')");
  }
  
  /* Case 16 */
  if (!(!isalpha ('\017'))) {
    failed ("Case 16: !isalpha ('\\017')");
  }
  
  /* Case 17 */
  if (!(!isalpha ('\020'))) {
    failed ("Case 17: !isalpha ('\\020')");
  }
  
  /* Case 18 */
  if (!(!isalpha ('\021'))) {
    failed ("Case 18: !isalpha ('\\021')");
  }
  
  /* Case 19 */
  if (!(!isalpha ('\022'))) {
    failed ("Case 19: !isalpha ('\\022')");
  }
  
  /* Case 20 */
  if (!(!isalpha ('\023'))) {
    failed ("Case 20: !isalpha ('\\023')");
  }
  
  /* Case 21 */
  if (!(!isalpha ('\024'))) {
    failed ("Case 21: !isalpha ('\\024')");
  }
  
  /* Case 22 */
  if (!(!isalpha ('\025'))) {
    failed ("Case 22: !isalpha ('\\025')");
  }
  
  /* Case 23 */
  if (!(!isalpha ('\026'))) {
    failed ("Case 23: !isalpha ('\\026')");
  }
  
  /* Case 24 */
  if (!(!isalpha ('\027'))) {
    failed ("Case 24: !isalpha ('\\027')");
  }
  
  /* Case 25 */
  if (!(!isalpha ('\030'))) {
    failed ("Case 25: !isalpha ('\\030')");
  }
  
  /* Case 26 */
  if (!(!isalpha ('\031'))) {
    failed ("Case 26: !isalpha ('\\031')");
  }
  
  /* Case 27 */
  if (!(!isalpha ('\032'))) {
    failed ("Case 27: !isalpha ('\\032')");
  }
  
  /* Case 28 */
  if (!(!isalpha ('\033'))) {
    failed ("Case 28: !isalpha ('\\033')");
  }
  
  /* Case 29 */
  if (!(!isalpha ('\034'))) {
    failed ("Case 29: !isalpha ('\\034')");
  }
  
  /* Case 30 */
  if (!(!isalpha ('\035'))) {
    failed ("Case 30: !isalpha ('\\035')");
  }
  
  /* Case 31 */
  if (!(!isalpha ('\036'))) {
    failed ("Case 31: !isalpha ('\\036')");
  }
  
  /* Case 32 */
  if (!(!isalpha ('\037'))) {
    failed ("Case 32: !isalpha ('\\037')");
  }
  
  /* Case 33 */
  if (!(!isalpha (' '))) {
    failed ("Case 33: !isalpha (' ')");
  }
  
  /* Case 34 */
  if (!(!isalpha ('!'))) {
    failed ("Case 34: !isalpha ('!')");
  }
  
  /* Case 35 */
  if (!(!isalpha ('\"'))) {
    failed ("Case 35: !isalpha ('\\\"')");
  }
  
  /* Case 36 */
  if (!(!isalpha ('#'))) {
    failed ("Case 36: !isalpha ('#')");
  }
  
  /* Case 37 */
  if (!(!isalpha ('$'))) {
    failed ("Case 37: !isalpha ('$')");
  }
  
  /* Case 38 */
  if (!(!isalpha ('%'))) {
    failed ("Case 38: !isalpha ('%')");
  }
  
  /* Case 39 */
  if (!(!isalpha ('&'))) {
    failed ("Case 39: !isalpha ('&')");
  }
  
  /* Case 40 */
  if (!(!isalpha ('\''))) {
    failed ("Case 40: !isalpha ('\\'')");
  }
  
  /* Case 41 */
  if (!(!isalpha ('('))) {
    failed ("Case 41: !isalpha ('(')");
  }
  
  /* Case 42 */
  if (!(!isalpha (')'))) {
    failed ("Case 42: !isalpha (')')");
  }
  
  /* Case 43 */
  if (!(!isalpha ('*'))) {
    failed ("Case 43: !isalpha ('*')");
  }
  
  /* Case 44 */
  if (!(!isalpha ('+'))) {
    failed ("Case 44: !isalpha ('+')");
  }
  
  /* Case 45 */
  if (!(!isalpha (','))) {
    failed ("Case 45: !isalpha (',')");
  }
  
  /* Case 46 */
  if (!(!isalpha ('-'))) {
    failed ("Case 46: !isalpha ('-')");
  }
  
  /* Case 47 */
  if (!(!isalpha ('.'))) {
    failed ("Case 47: !isalpha ('.')");
  }
  
  /* Case 48 */
  if (!(!isalpha ('/'))) {
    failed ("Case 48: !isalpha ('/')");
  }
  
  /* Case 49 */
  if (!(!isalpha ('0'))) {
    failed ("Case 49: !isalpha ('0')");
  }
  
  /* Case 50 */
  if (!(!isalpha ('1'))) {
    failed ("Case 50: !isalpha ('1')");
  }
  
  /* Case 51 */
  if (!(!isalpha ('2'))) {
    failed ("Case 51: !isalpha ('2')");
  }
  
  /* Case 52 */
  if (!(!isalpha ('3'))) {
    failed ("Case 52: !isalpha ('3')");
  }
  
  /* Case 53 */
  if (!(!isalpha ('4'))) {
    failed ("Case 53: !isalpha ('4')");
  }
  
  /* Case 54 */
  if (!(!isalpha ('5'))) {
    failed ("Case 54: !isalpha ('5')");
  }
  
  /* Case 55 */
  if (!(!isalpha ('6'))) {
    failed ("Case 55: !isalpha ('6')");
  }
  
  /* Case 56 */
  if (!(!isalpha ('7'))) {
    failed ("Case 56: !isalpha ('7')");
  }
  
  /* Case 57 */
  if (!(!isalpha ('8'))) {
    failed ("Case 57: !isalpha ('8')");
  }
  
  /* Case 58 */
  if (!(!isalpha ('9'))) {
    failed ("Case 58: !isalpha ('9')");
  }
  
  /* Case 59 */
  if (!(!isalpha (':'))) {
    failed ("Case 59: !isalpha (':')");
  }
  
  /* Case 60 */
  if (!(!isalpha (';'))) {
    failed ("Case 60: !isalpha (';')");
  }
  
  /* Case 61 */
  if (!(!isalpha ('<'))) {
    failed ("Case 61: !isalpha ('<')");
  }
  
  /* Case 62 */
  if (!(!isalpha ('='))) {
    failed ("Case 62: !isalpha ('=')");
  }
  
  /* Case 63 */
  if (!(!isalpha ('>'))) {
    failed ("Case 63: !isalpha ('>')");
  }
  
  /* Case 64 */
  if (!(!isalpha ('?'))) {
    failed ("Case 64: !isalpha ('?')");
  }
  
  /* Case 65 */
  if (!(!isalpha ('@'))) {
    failed ("Case 65: !isalpha ('@')");
  }
  
  /* Case 66 */
  if (!(isalpha ('A'))) {
    failed ("Case 66: isalpha ('A')");
  }
  
  /* Case 67 */
  if (!(isalpha ('B'))) {
    failed ("Case 67: isalpha ('B')");
  }
  
  /* Case 68 */
  if (!(isalpha ('C'))) {
    failed ("Case 68: isalpha ('C')");
  }
  
  /* Case 69 */
  if (!(isalpha ('D'))) {
    failed ("Case 69: isalpha ('D')");
  }
  
  /* Case 70 */
  if (!(isalpha ('E'))) {
    failed ("Case 70: isalpha ('E')");
  }
  
  /* Case 71 */
  if (!(isalpha ('F'))) {
    failed ("Case 71: isalpha ('F')");
  }
  
  /* Case 72 */
  if (!(isalpha ('G'))) {
    failed ("Case 72: isalpha ('G')");
  }
  
  /* Case 73 */
  if (!(isalpha ('H'))) {
    failed ("Case 73: isalpha ('H')");
  }
  
  /* Case 74 */
  if (!(isalpha ('I'))) {
    failed ("Case 74: isalpha ('I')");
  }
  
  /* Case 75 */
  if (!(isalpha ('J'))) {
    failed ("Case 75: isalpha ('J')");
  }
  
  /* Case 76 */
  if (!(isalpha ('K'))) {
    failed ("Case 76: isalpha ('K')");
  }
  
  /* Case 77 */
  if (!(isalpha ('L'))) {
    failed ("Case 77: isalpha ('L')");
  }
  
  /* Case 78 */
  if (!(isalpha ('M'))) {
    failed ("Case 78: isalpha ('M')");
  }
  
  /* Case 79 */
  if (!(isalpha ('N'))) {
    failed ("Case 79: isalpha ('N')");
  }
  
  /* Case 80 */
  if (!(isalpha ('O'))) {
    failed ("Case 80: isalpha ('O')");
  }
  
  /* Case 81 */
  if (!(isalpha ('P'))) {
    failed ("Case 81: isalpha ('P')");
  }
  
  /* Case 82 */
  if (!(isalpha ('Q'))) {
    failed ("Case 82: isalpha ('Q')");
  }
  
  /* Case 83 */
  if (!(isalpha ('R'))) {
    failed ("Case 83: isalpha ('R')");
  }
  
  /* Case 84 */
  if (!(isalpha ('S'))) {
    failed ("Case 84: isalpha ('S')");
  }
  
  /* Case 85 */
  if (!(isalpha ('T'))) {
    failed ("Case 85: isalpha ('T')");
  }
  
  /* Case 86 */
  if (!(isalpha ('U'))) {
    failed ("Case 86: isalpha ('U')");
  }
  
  /* Case 87 */
  if (!(isalpha ('V'))) {
    failed ("Case 87: isalpha ('V')");
  }
  
  /* Case 88 */
  if (!(isalpha ('W'))) {
    failed ("Case 88: isalpha ('W')");
  }
  
  /* Case 89 */
  if (!(isalpha ('X'))) {
    failed ("Case 89: isalpha ('X')");
  }
  
  /* Case 90 */
  if (!(isalpha ('Y'))) {
    failed ("Case 90: isalpha ('Y')");
  }
  
  /* Case 91 */
  if (!(isalpha ('Z'))) {
    failed ("Case 91: isalpha ('Z')");
  }
  
  /* Case 92 */
  if (!(!isalpha ('['))) {
    failed ("Case 92: !isalpha ('[')");
  }
  
  /* Case 93 */
  if (!(!isalpha ('\\'))) {
    failed ("Case 93: !isalpha ('\\\\')");
  }
  
  /* Case 94 */
  if (!(!isalpha (']'))) {
    failed ("Case 94: !isalpha (']')");
  }
  
  /* Case 95 */
  if (!(!isalpha ('^'))) {
    failed ("Case 95: !isalpha ('^')");
  }
  
  /* Case 96 */
  if (!(!isalpha ('_'))) {
    failed ("Case 96: !isalpha ('_')");
  }
  
  /* Case 97 */
  if (!(!isalpha ('`'))) {
    failed ("Case 97: !isalpha ('`')");
  }
  
  /* Case 98 */
  if (!(isalpha ('a'))) {
    failed ("Case 98: isalpha ('a')");
  }
  
  /* Case 99 */
  if (!(isalpha ('b'))) {
    failed ("Case 99: isalpha ('b')");
  }
  
  /* Case 100 */
  if (!(isalpha ('c'))) {
    failed ("Case 100: isalpha ('c')");
  }
  
  /* Case 101 */
  if (!(isalpha ('d'))) {
    failed ("Case 101: isalpha ('d')");
  }
  
  /* Case 102 */
  if (!(isalpha ('e'))) {
    failed ("Case 102: isalpha ('e')");
  }
  
  /* Case 103 */
  if (!(isalpha ('f'))) {
    failed ("Case 103: isalpha ('f')");
  }
  
  /* Case 104 */
  if (!(isalpha ('g'))) {
    failed ("Case 104: isalpha ('g')");
  }
  
  /* Case 105 */
  if (!(isalpha ('h'))) {
    failed ("Case 105: isalpha ('h')");
  }
  
  /* Case 106 */
  if (!(isalpha ('i'))) {
    failed ("Case 106: isalpha ('i')");
  }
  
  /* Case 107 */
  if (!(isalpha ('j'))) {
    failed ("Case 107: isalpha ('j')");
  }
  
  /* Case 108 */
  if (!(isalpha ('k'))) {
    failed ("Case 108: isalpha ('k')");
  }
  
  /* Case 109 */
  if (!(isalpha ('l'))) {
    failed ("Case 109: isalpha ('l')");
  }
  
  /* Case 110 */
  if (!(isalpha ('m'))) {
    failed ("Case 110: isalpha ('m')");
  }
  
  /* Case 111 */
  if (!(isalpha ('n'))) {
    failed ("Case 111: isalpha ('n')");
  }
  
  /* Case 112 */
  if (!(isalpha ('o'))) {
    failed ("Case 112: isalpha ('o')");
  }
  
  /* Case 113 */
  if (!(isalpha ('p'))) {
    failed ("Case 113: isalpha ('p')");
  }
  
  /* Case 114 */
  if (!(isalpha ('q'))) {
    failed ("Case 114: isalpha ('q')");
  }
  
  /* Case 115 */
  if (!(isalpha ('r'))) {
    failed ("Case 115: isalpha ('r')");
  }
  
  /* Case 116 */
  if (!(isalpha ('s'))) {
    failed ("Case 116: isalpha ('s')");
  }
  
  /* Case 117 */
  if (!(isalpha ('t'))) {
    failed ("Case 117: isalpha ('t')");
  }
  
  /* Case 118 */
  if (!(isalpha ('u'))) {
    failed ("Case 118: isalpha ('u')");
  }
  
  /* Case 119 */
  if (!(isalpha ('v'))) {
    failed ("Case 119: isalpha ('v')");
  }
  
  /* Case 120 */
  if (!(isalpha ('w'))) {
    failed ("Case 120: isalpha ('w')");
  }
  
  /* Case 121 */
  if (!(isalpha ('x'))) {
    failed ("Case 121: isalpha ('x')");
  }
  
  /* Case 122 */
  if (!(isalpha ('y'))) {
    failed ("Case 122: isalpha ('y')");
  }
  
  /* Case 123 */
  if (!(isalpha ('z'))) {
    failed ("Case 123: isalpha ('z')");
  }
  
  /* Case 124 */
  if (!(!isalpha ('{'))) {
    failed ("Case 124: !isalpha ('{')");
  }
  
  /* Case 125 */
  if (!(!isalpha ('|'))) {
    failed ("Case 125: !isalpha ('|')");
  }
  
  /* Case 126 */
  if (!(!isalpha ('}'))) {
    failed ("Case 126: !isalpha ('}')");
  }
  
  /* Case 127 */
  if (!(!isalpha ('~'))) {
    failed ("Case 127: !isalpha ('~')");
  }
  
  /* Case 128 */
  if (!(!isalpha ('\177'))) {
    failed ("Case 128: !isalpha ('\\177')");
  }
  
}


void main ()
{
  test ("test-isalpha", "Test for ANSI Standard C: 7.3.1.2");

  do_test ();

  result ();
}

