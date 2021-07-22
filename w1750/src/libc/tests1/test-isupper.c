/*
 * Test for ANSI Standard C: 7.3.1.10
 * 
 * #include <ctype.h>
 * int isupper (int c);
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


static char *_test_isupper_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(!isupper ('\000'))) {
    failed ("Case 1: !isupper ('\\000')");
  }
  
  /* Case 2 */
  if (!(!isupper ('\001'))) {
    failed ("Case 2: !isupper ('\\001')");
  }
  
  /* Case 3 */
  if (!(!isupper ('\002'))) {
    failed ("Case 3: !isupper ('\\002')");
  }
  
  /* Case 4 */
  if (!(!isupper ('\003'))) {
    failed ("Case 4: !isupper ('\\003')");
  }
  
  /* Case 5 */
  if (!(!isupper ('\004'))) {
    failed ("Case 5: !isupper ('\\004')");
  }
  
  /* Case 6 */
  if (!(!isupper ('\005'))) {
    failed ("Case 6: !isupper ('\\005')");
  }
  
  /* Case 7 */
  if (!(!isupper ('\006'))) {
    failed ("Case 7: !isupper ('\\006')");
  }
  
  /* Case 8 */
  if (!(!isupper ('\007'))) {
    failed ("Case 8: !isupper ('\\007')");
  }
  
  /* Case 9 */
  if (!(!isupper ('\010'))) {
    failed ("Case 9: !isupper ('\\010')");
  }
  
  /* Case 10 */
  if (!(!isupper ('\011'))) {
    failed ("Case 10: !isupper ('\\011')");
  }
  
  /* Case 11 */
  if (!(!isupper ('\012'))) {
    failed ("Case 11: !isupper ('\\012')");
  }
  
  /* Case 12 */
  if (!(!isupper ('\013'))) {
    failed ("Case 12: !isupper ('\\013')");
  }
  
  /* Case 13 */
  if (!(!isupper ('\014'))) {
    failed ("Case 13: !isupper ('\\014')");
  }
  
  /* Case 14 */
  if (!(!isupper ('\015'))) {
    failed ("Case 14: !isupper ('\\015')");
  }
  
  /* Case 15 */
  if (!(!isupper ('\016'))) {
    failed ("Case 15: !isupper ('\\016')");
  }
  
  /* Case 16 */
  if (!(!isupper ('\017'))) {
    failed ("Case 16: !isupper ('\\017')");
  }
  
  /* Case 17 */
  if (!(!isupper ('\020'))) {
    failed ("Case 17: !isupper ('\\020')");
  }
  
  /* Case 18 */
  if (!(!isupper ('\021'))) {
    failed ("Case 18: !isupper ('\\021')");
  }
  
  /* Case 19 */
  if (!(!isupper ('\022'))) {
    failed ("Case 19: !isupper ('\\022')");
  }
  
  /* Case 20 */
  if (!(!isupper ('\023'))) {
    failed ("Case 20: !isupper ('\\023')");
  }
  
  /* Case 21 */
  if (!(!isupper ('\024'))) {
    failed ("Case 21: !isupper ('\\024')");
  }
  
  /* Case 22 */
  if (!(!isupper ('\025'))) {
    failed ("Case 22: !isupper ('\\025')");
  }
  
  /* Case 23 */
  if (!(!isupper ('\026'))) {
    failed ("Case 23: !isupper ('\\026')");
  }
  
  /* Case 24 */
  if (!(!isupper ('\027'))) {
    failed ("Case 24: !isupper ('\\027')");
  }
  
  /* Case 25 */
  if (!(!isupper ('\030'))) {
    failed ("Case 25: !isupper ('\\030')");
  }
  
  /* Case 26 */
  if (!(!isupper ('\031'))) {
    failed ("Case 26: !isupper ('\\031')");
  }
  
  /* Case 27 */
  if (!(!isupper ('\032'))) {
    failed ("Case 27: !isupper ('\\032')");
  }
  
  /* Case 28 */
  if (!(!isupper ('\033'))) {
    failed ("Case 28: !isupper ('\\033')");
  }
  
  /* Case 29 */
  if (!(!isupper ('\034'))) {
    failed ("Case 29: !isupper ('\\034')");
  }
  
  /* Case 30 */
  if (!(!isupper ('\035'))) {
    failed ("Case 30: !isupper ('\\035')");
  }
  
  /* Case 31 */
  if (!(!isupper ('\036'))) {
    failed ("Case 31: !isupper ('\\036')");
  }
  
  /* Case 32 */
  if (!(!isupper ('\037'))) {
    failed ("Case 32: !isupper ('\\037')");
  }
  
  /* Case 33 */
  if (!(!isupper (' '))) {
    failed ("Case 33: !isupper (' ')");
  }
  
  /* Case 34 */
  if (!(!isupper ('!'))) {
    failed ("Case 34: !isupper ('!')");
  }
  
  /* Case 35 */
  if (!(!isupper ('\"'))) {
    failed ("Case 35: !isupper ('\\\"')");
  }
  
  /* Case 36 */
  if (!(!isupper ('#'))) {
    failed ("Case 36: !isupper ('#')");
  }
  
  /* Case 37 */
  if (!(!isupper ('$'))) {
    failed ("Case 37: !isupper ('$')");
  }
  
  /* Case 38 */
  if (!(!isupper ('%'))) {
    failed ("Case 38: !isupper ('%')");
  }
  
  /* Case 39 */
  if (!(!isupper ('&'))) {
    failed ("Case 39: !isupper ('&')");
  }
  
  /* Case 40 */
  if (!(!isupper ('\''))) {
    failed ("Case 40: !isupper ('\\'')");
  }
  
  /* Case 41 */
  if (!(!isupper ('('))) {
    failed ("Case 41: !isupper ('(')");
  }
  
  /* Case 42 */
  if (!(!isupper (')'))) {
    failed ("Case 42: !isupper (')')");
  }
  
  /* Case 43 */
  if (!(!isupper ('*'))) {
    failed ("Case 43: !isupper ('*')");
  }
  
  /* Case 44 */
  if (!(!isupper ('+'))) {
    failed ("Case 44: !isupper ('+')");
  }
  
  /* Case 45 */
  if (!(!isupper (','))) {
    failed ("Case 45: !isupper (',')");
  }
  
  /* Case 46 */
  if (!(!isupper ('-'))) {
    failed ("Case 46: !isupper ('-')");
  }
  
  /* Case 47 */
  if (!(!isupper ('.'))) {
    failed ("Case 47: !isupper ('.')");
  }
  
  /* Case 48 */
  if (!(!isupper ('/'))) {
    failed ("Case 48: !isupper ('/')");
  }
  
  /* Case 49 */
  if (!(!isupper ('0'))) {
    failed ("Case 49: !isupper ('0')");
  }
  
  /* Case 50 */
  if (!(!isupper ('1'))) {
    failed ("Case 50: !isupper ('1')");
  }
  
  /* Case 51 */
  if (!(!isupper ('2'))) {
    failed ("Case 51: !isupper ('2')");
  }
  
  /* Case 52 */
  if (!(!isupper ('3'))) {
    failed ("Case 52: !isupper ('3')");
  }
  
  /* Case 53 */
  if (!(!isupper ('4'))) {
    failed ("Case 53: !isupper ('4')");
  }
  
  /* Case 54 */
  if (!(!isupper ('5'))) {
    failed ("Case 54: !isupper ('5')");
  }
  
  /* Case 55 */
  if (!(!isupper ('6'))) {
    failed ("Case 55: !isupper ('6')");
  }
  
  /* Case 56 */
  if (!(!isupper ('7'))) {
    failed ("Case 56: !isupper ('7')");
  }
  
  /* Case 57 */
  if (!(!isupper ('8'))) {
    failed ("Case 57: !isupper ('8')");
  }
  
  /* Case 58 */
  if (!(!isupper ('9'))) {
    failed ("Case 58: !isupper ('9')");
  }
  
  /* Case 59 */
  if (!(!isupper (':'))) {
    failed ("Case 59: !isupper (':')");
  }
  
  /* Case 60 */
  if (!(!isupper (';'))) {
    failed ("Case 60: !isupper (';')");
  }
  
  /* Case 61 */
  if (!(!isupper ('<'))) {
    failed ("Case 61: !isupper ('<')");
  }
  
  /* Case 62 */
  if (!(!isupper ('='))) {
    failed ("Case 62: !isupper ('=')");
  }
  
  /* Case 63 */
  if (!(!isupper ('>'))) {
    failed ("Case 63: !isupper ('>')");
  }
  
  /* Case 64 */
  if (!(!isupper ('?'))) {
    failed ("Case 64: !isupper ('?')");
  }
  
  /* Case 65 */
  if (!(!isupper ('@'))) {
    failed ("Case 65: !isupper ('@')");
  }
  
  /* Case 66 */
  if (!(isupper ('A'))) {
    failed ("Case 66: isupper ('A')");
  }
  
  /* Case 67 */
  if (!(isupper ('B'))) {
    failed ("Case 67: isupper ('B')");
  }
  
  /* Case 68 */
  if (!(isupper ('C'))) {
    failed ("Case 68: isupper ('C')");
  }
  
  /* Case 69 */
  if (!(isupper ('D'))) {
    failed ("Case 69: isupper ('D')");
  }
  
  /* Case 70 */
  if (!(isupper ('E'))) {
    failed ("Case 70: isupper ('E')");
  }
  
  /* Case 71 */
  if (!(isupper ('F'))) {
    failed ("Case 71: isupper ('F')");
  }
  
  /* Case 72 */
  if (!(isupper ('G'))) {
    failed ("Case 72: isupper ('G')");
  }
  
  /* Case 73 */
  if (!(isupper ('H'))) {
    failed ("Case 73: isupper ('H')");
  }
  
  /* Case 74 */
  if (!(isupper ('I'))) {
    failed ("Case 74: isupper ('I')");
  }
  
  /* Case 75 */
  if (!(isupper ('J'))) {
    failed ("Case 75: isupper ('J')");
  }
  
  /* Case 76 */
  if (!(isupper ('K'))) {
    failed ("Case 76: isupper ('K')");
  }
  
  /* Case 77 */
  if (!(isupper ('L'))) {
    failed ("Case 77: isupper ('L')");
  }
  
  /* Case 78 */
  if (!(isupper ('M'))) {
    failed ("Case 78: isupper ('M')");
  }
  
  /* Case 79 */
  if (!(isupper ('N'))) {
    failed ("Case 79: isupper ('N')");
  }
  
  /* Case 80 */
  if (!(isupper ('O'))) {
    failed ("Case 80: isupper ('O')");
  }
  
  /* Case 81 */
  if (!(isupper ('P'))) {
    failed ("Case 81: isupper ('P')");
  }
  
  /* Case 82 */
  if (!(isupper ('Q'))) {
    failed ("Case 82: isupper ('Q')");
  }
  
  /* Case 83 */
  if (!(isupper ('R'))) {
    failed ("Case 83: isupper ('R')");
  }
  
  /* Case 84 */
  if (!(isupper ('S'))) {
    failed ("Case 84: isupper ('S')");
  }
  
  /* Case 85 */
  if (!(isupper ('T'))) {
    failed ("Case 85: isupper ('T')");
  }
  
  /* Case 86 */
  if (!(isupper ('U'))) {
    failed ("Case 86: isupper ('U')");
  }
  
  /* Case 87 */
  if (!(isupper ('V'))) {
    failed ("Case 87: isupper ('V')");
  }
  
  /* Case 88 */
  if (!(isupper ('W'))) {
    failed ("Case 88: isupper ('W')");
  }
  
  /* Case 89 */
  if (!(isupper ('X'))) {
    failed ("Case 89: isupper ('X')");
  }
  
  /* Case 90 */
  if (!(isupper ('Y'))) {
    failed ("Case 90: isupper ('Y')");
  }
  
  /* Case 91 */
  if (!(isupper ('Z'))) {
    failed ("Case 91: isupper ('Z')");
  }
  
  /* Case 92 */
  if (!(!isupper ('['))) {
    failed ("Case 92: !isupper ('[')");
  }
  
  /* Case 93 */
  if (!(!isupper ('\\'))) {
    failed ("Case 93: !isupper ('\\\\')");
  }
  
  /* Case 94 */
  if (!(!isupper (']'))) {
    failed ("Case 94: !isupper (']')");
  }
  
  /* Case 95 */
  if (!(!isupper ('^'))) {
    failed ("Case 95: !isupper ('^')");
  }
  
  /* Case 96 */
  if (!(!isupper ('_'))) {
    failed ("Case 96: !isupper ('_')");
  }
  
  /* Case 97 */
  if (!(!isupper ('`'))) {
    failed ("Case 97: !isupper ('`')");
  }
  
  /* Case 98 */
  if (!(!isupper ('a'))) {
    failed ("Case 98: !isupper ('a')");
  }
  
  /* Case 99 */
  if (!(!isupper ('b'))) {
    failed ("Case 99: !isupper ('b')");
  }
  
  /* Case 100 */
  if (!(!isupper ('c'))) {
    failed ("Case 100: !isupper ('c')");
  }
  
  /* Case 101 */
  if (!(!isupper ('d'))) {
    failed ("Case 101: !isupper ('d')");
  }
  
  /* Case 102 */
  if (!(!isupper ('e'))) {
    failed ("Case 102: !isupper ('e')");
  }
  
  /* Case 103 */
  if (!(!isupper ('f'))) {
    failed ("Case 103: !isupper ('f')");
  }
  
  /* Case 104 */
  if (!(!isupper ('g'))) {
    failed ("Case 104: !isupper ('g')");
  }
  
  /* Case 105 */
  if (!(!isupper ('h'))) {
    failed ("Case 105: !isupper ('h')");
  }
  
  /* Case 106 */
  if (!(!isupper ('i'))) {
    failed ("Case 106: !isupper ('i')");
  }
  
  /* Case 107 */
  if (!(!isupper ('j'))) {
    failed ("Case 107: !isupper ('j')");
  }
  
  /* Case 108 */
  if (!(!isupper ('k'))) {
    failed ("Case 108: !isupper ('k')");
  }
  
  /* Case 109 */
  if (!(!isupper ('l'))) {
    failed ("Case 109: !isupper ('l')");
  }
  
  /* Case 110 */
  if (!(!isupper ('m'))) {
    failed ("Case 110: !isupper ('m')");
  }
  
  /* Case 111 */
  if (!(!isupper ('n'))) {
    failed ("Case 111: !isupper ('n')");
  }
  
  /* Case 112 */
  if (!(!isupper ('o'))) {
    failed ("Case 112: !isupper ('o')");
  }
  
  /* Case 113 */
  if (!(!isupper ('p'))) {
    failed ("Case 113: !isupper ('p')");
  }
  
  /* Case 114 */
  if (!(!isupper ('q'))) {
    failed ("Case 114: !isupper ('q')");
  }
  
  /* Case 115 */
  if (!(!isupper ('r'))) {
    failed ("Case 115: !isupper ('r')");
  }
  
  /* Case 116 */
  if (!(!isupper ('s'))) {
    failed ("Case 116: !isupper ('s')");
  }
  
  /* Case 117 */
  if (!(!isupper ('t'))) {
    failed ("Case 117: !isupper ('t')");
  }
  
  /* Case 118 */
  if (!(!isupper ('u'))) {
    failed ("Case 118: !isupper ('u')");
  }
  
  /* Case 119 */
  if (!(!isupper ('v'))) {
    failed ("Case 119: !isupper ('v')");
  }
  
  /* Case 120 */
  if (!(!isupper ('w'))) {
    failed ("Case 120: !isupper ('w')");
  }
  
  /* Case 121 */
  if (!(!isupper ('x'))) {
    failed ("Case 121: !isupper ('x')");
  }
  
  /* Case 122 */
  if (!(!isupper ('y'))) {
    failed ("Case 122: !isupper ('y')");
  }
  
  /* Case 123 */
  if (!(!isupper ('z'))) {
    failed ("Case 123: !isupper ('z')");
  }
  
  /* Case 124 */
  if (!(!isupper ('{'))) {
    failed ("Case 124: !isupper ('{')");
  }
  
  /* Case 125 */
  if (!(!isupper ('|'))) {
    failed ("Case 125: !isupper ('|')");
  }
  
  /* Case 126 */
  if (!(!isupper ('}'))) {
    failed ("Case 126: !isupper ('}')");
  }
  
  /* Case 127 */
  if (!(!isupper ('~'))) {
    failed ("Case 127: !isupper ('~')");
  }
  
  /* Case 128 */
  if (!(!isupper ('\177'))) {
    failed ("Case 128: !isupper ('\\177')");
  }
  
}


void main ()
{
  test ("test-isupper", "Test for ANSI Standard C: 7.3.1.10");

  do_test ();

  result ();
}

