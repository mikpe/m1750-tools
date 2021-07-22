/*
 * Test for ANSI Standard C: 7.3.2.2
 * 
 * #include <ctype.h>
 * int toupper (int c);
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


static char *_test_toupper_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(toupper ('\000') == '\000')) {
    failed ("Case 1: toupper ('\\000') == '\\000'");
  }
  
  /* Case 2 */
  if (!(toupper ('\001') == '\001')) {
    failed ("Case 2: toupper ('\\001') == '\\001'");
  }
  
  /* Case 3 */
  if (!(toupper ('\002') == '\002')) {
    failed ("Case 3: toupper ('\\002') == '\\002'");
  }
  
  /* Case 4 */
  if (!(toupper ('\003') == '\003')) {
    failed ("Case 4: toupper ('\\003') == '\\003'");
  }
  
  /* Case 5 */
  if (!(toupper ('\004') == '\004')) {
    failed ("Case 5: toupper ('\\004') == '\\004'");
  }
  
  /* Case 6 */
  if (!(toupper ('\005') == '\005')) {
    failed ("Case 6: toupper ('\\005') == '\\005'");
  }
  
  /* Case 7 */
  if (!(toupper ('\006') == '\006')) {
    failed ("Case 7: toupper ('\\006') == '\\006'");
  }
  
  /* Case 8 */
  if (!(toupper ('\007') == '\007')) {
    failed ("Case 8: toupper ('\\007') == '\\007'");
  }
  
  /* Case 9 */
  if (!(toupper ('\010') == '\010')) {
    failed ("Case 9: toupper ('\\010') == '\\010'");
  }
  
  /* Case 10 */
  if (!(toupper ('\011') == '\011')) {
    failed ("Case 10: toupper ('\\011') == '\\011'");
  }
  
  /* Case 11 */
  if (!(toupper ('\012') == '\012')) {
    failed ("Case 11: toupper ('\\012') == '\\012'");
  }
  
  /* Case 12 */
  if (!(toupper ('\013') == '\013')) {
    failed ("Case 12: toupper ('\\013') == '\\013'");
  }
  
  /* Case 13 */
  if (!(toupper ('\014') == '\014')) {
    failed ("Case 13: toupper ('\\014') == '\\014'");
  }
  
  /* Case 14 */
  if (!(toupper ('\015') == '\015')) {
    failed ("Case 14: toupper ('\\015') == '\\015'");
  }
  
  /* Case 15 */
  if (!(toupper ('\016') == '\016')) {
    failed ("Case 15: toupper ('\\016') == '\\016'");
  }
  
  /* Case 16 */
  if (!(toupper ('\017') == '\017')) {
    failed ("Case 16: toupper ('\\017') == '\\017'");
  }
  
  /* Case 17 */
  if (!(toupper ('\020') == '\020')) {
    failed ("Case 17: toupper ('\\020') == '\\020'");
  }
  
  /* Case 18 */
  if (!(toupper ('\021') == '\021')) {
    failed ("Case 18: toupper ('\\021') == '\\021'");
  }
  
  /* Case 19 */
  if (!(toupper ('\022') == '\022')) {
    failed ("Case 19: toupper ('\\022') == '\\022'");
  }
  
  /* Case 20 */
  if (!(toupper ('\023') == '\023')) {
    failed ("Case 20: toupper ('\\023') == '\\023'");
  }
  
  /* Case 21 */
  if (!(toupper ('\024') == '\024')) {
    failed ("Case 21: toupper ('\\024') == '\\024'");
  }
  
  /* Case 22 */
  if (!(toupper ('\025') == '\025')) {
    failed ("Case 22: toupper ('\\025') == '\\025'");
  }
  
  /* Case 23 */
  if (!(toupper ('\026') == '\026')) {
    failed ("Case 23: toupper ('\\026') == '\\026'");
  }
  
  /* Case 24 */
  if (!(toupper ('\027') == '\027')) {
    failed ("Case 24: toupper ('\\027') == '\\027'");
  }
  
  /* Case 25 */
  if (!(toupper ('\030') == '\030')) {
    failed ("Case 25: toupper ('\\030') == '\\030'");
  }
  
  /* Case 26 */
  if (!(toupper ('\031') == '\031')) {
    failed ("Case 26: toupper ('\\031') == '\\031'");
  }
  
  /* Case 27 */
  if (!(toupper ('\032') == '\032')) {
    failed ("Case 27: toupper ('\\032') == '\\032'");
  }
  
  /* Case 28 */
  if (!(toupper ('\033') == '\033')) {
    failed ("Case 28: toupper ('\\033') == '\\033'");
  }
  
  /* Case 29 */
  if (!(toupper ('\034') == '\034')) {
    failed ("Case 29: toupper ('\\034') == '\\034'");
  }
  
  /* Case 30 */
  if (!(toupper ('\035') == '\035')) {
    failed ("Case 30: toupper ('\\035') == '\\035'");
  }
  
  /* Case 31 */
  if (!(toupper ('\036') == '\036')) {
    failed ("Case 31: toupper ('\\036') == '\\036'");
  }
  
  /* Case 32 */
  if (!(toupper ('\037') == '\037')) {
    failed ("Case 32: toupper ('\\037') == '\\037'");
  }
  
  /* Case 33 */
  if (!(toupper (' ') == ' ')) {
    failed ("Case 33: toupper (' ') == ' '");
  }
  
  /* Case 34 */
  if (!(toupper ('!') == '!')) {
    failed ("Case 34: toupper ('!') == '!'");
  }
  
  /* Case 35 */
  if (!(toupper ('\"') == '\"')) {
    failed ("Case 35: toupper ('\\\"') == '\\\"'");
  }
  
  /* Case 36 */
  if (!(toupper ('#') == '#')) {
    failed ("Case 36: toupper ('#') == '#'");
  }
  
  /* Case 37 */
  if (!(toupper ('$') == '$')) {
    failed ("Case 37: toupper ('$') == '$'");
  }
  
  /* Case 38 */
  if (!(toupper ('%') == '%')) {
    failed ("Case 38: toupper ('%') == '%'");
  }
  
  /* Case 39 */
  if (!(toupper ('&') == '&')) {
    failed ("Case 39: toupper ('&') == '&'");
  }
  
  /* Case 40 */
  if (!(toupper ('\'') == '\'')) {
    failed ("Case 40: toupper ('\\'') == '\\''");
  }
  
  /* Case 41 */
  if (!(toupper ('(') == '(')) {
    failed ("Case 41: toupper ('(') == '('");
  }
  
  /* Case 42 */
  if (!(toupper (')') == ')')) {
    failed ("Case 42: toupper (')') == ')'");
  }
  
  /* Case 43 */
  if (!(toupper ('*') == '*')) {
    failed ("Case 43: toupper ('*') == '*'");
  }
  
  /* Case 44 */
  if (!(toupper ('+') == '+')) {
    failed ("Case 44: toupper ('+') == '+'");
  }
  
  /* Case 45 */
  if (!(toupper (',') == ',')) {
    failed ("Case 45: toupper (',') == ','");
  }
  
  /* Case 46 */
  if (!(toupper ('-') == '-')) {
    failed ("Case 46: toupper ('-') == '-'");
  }
  
  /* Case 47 */
  if (!(toupper ('.') == '.')) {
    failed ("Case 47: toupper ('.') == '.'");
  }
  
  /* Case 48 */
  if (!(toupper ('/') == '/')) {
    failed ("Case 48: toupper ('/') == '/'");
  }
  
  /* Case 49 */
  if (!(toupper ('0') == '0')) {
    failed ("Case 49: toupper ('0') == '0'");
  }
  
  /* Case 50 */
  if (!(toupper ('1') == '1')) {
    failed ("Case 50: toupper ('1') == '1'");
  }
  
  /* Case 51 */
  if (!(toupper ('2') == '2')) {
    failed ("Case 51: toupper ('2') == '2'");
  }
  
  /* Case 52 */
  if (!(toupper ('3') == '3')) {
    failed ("Case 52: toupper ('3') == '3'");
  }
  
  /* Case 53 */
  if (!(toupper ('4') == '4')) {
    failed ("Case 53: toupper ('4') == '4'");
  }
  
  /* Case 54 */
  if (!(toupper ('5') == '5')) {
    failed ("Case 54: toupper ('5') == '5'");
  }
  
  /* Case 55 */
  if (!(toupper ('6') == '6')) {
    failed ("Case 55: toupper ('6') == '6'");
  }
  
  /* Case 56 */
  if (!(toupper ('7') == '7')) {
    failed ("Case 56: toupper ('7') == '7'");
  }
  
  /* Case 57 */
  if (!(toupper ('8') == '8')) {
    failed ("Case 57: toupper ('8') == '8'");
  }
  
  /* Case 58 */
  if (!(toupper ('9') == '9')) {
    failed ("Case 58: toupper ('9') == '9'");
  }
  
  /* Case 59 */
  if (!(toupper (':') == ':')) {
    failed ("Case 59: toupper (':') == ':'");
  }
  
  /* Case 60 */
  if (!(toupper (';') == ';')) {
    failed ("Case 60: toupper (';') == ';'");
  }
  
  /* Case 61 */
  if (!(toupper ('<') == '<')) {
    failed ("Case 61: toupper ('<') == '<'");
  }
  
  /* Case 62 */
  if (!(toupper ('=') == '=')) {
    failed ("Case 62: toupper ('=') == '='");
  }
  
  /* Case 63 */
  if (!(toupper ('>') == '>')) {
    failed ("Case 63: toupper ('>') == '>'");
  }
  
  /* Case 64 */
  if (!(toupper ('?') == '?')) {
    failed ("Case 64: toupper ('?') == '?'");
  }
  
  /* Case 65 */
  if (!(toupper ('@') == '@')) {
    failed ("Case 65: toupper ('@') == '@'");
  }
  
  /* Case 66 */
  if (!(toupper ('A') == 'A')) {
    failed ("Case 66: toupper ('A') == 'A'");
  }
  
  /* Case 67 */
  if (!(toupper ('B') == 'B')) {
    failed ("Case 67: toupper ('B') == 'B'");
  }
  
  /* Case 68 */
  if (!(toupper ('C') == 'C')) {
    failed ("Case 68: toupper ('C') == 'C'");
  }
  
  /* Case 69 */
  if (!(toupper ('D') == 'D')) {
    failed ("Case 69: toupper ('D') == 'D'");
  }
  
  /* Case 70 */
  if (!(toupper ('E') == 'E')) {
    failed ("Case 70: toupper ('E') == 'E'");
  }
  
  /* Case 71 */
  if (!(toupper ('F') == 'F')) {
    failed ("Case 71: toupper ('F') == 'F'");
  }
  
  /* Case 72 */
  if (!(toupper ('G') == 'G')) {
    failed ("Case 72: toupper ('G') == 'G'");
  }
  
  /* Case 73 */
  if (!(toupper ('H') == 'H')) {
    failed ("Case 73: toupper ('H') == 'H'");
  }
  
  /* Case 74 */
  if (!(toupper ('I') == 'I')) {
    failed ("Case 74: toupper ('I') == 'I'");
  }
  
  /* Case 75 */
  if (!(toupper ('J') == 'J')) {
    failed ("Case 75: toupper ('J') == 'J'");
  }
  
  /* Case 76 */
  if (!(toupper ('K') == 'K')) {
    failed ("Case 76: toupper ('K') == 'K'");
  }
  
  /* Case 77 */
  if (!(toupper ('L') == 'L')) {
    failed ("Case 77: toupper ('L') == 'L'");
  }
  
  /* Case 78 */
  if (!(toupper ('M') == 'M')) {
    failed ("Case 78: toupper ('M') == 'M'");
  }
  
  /* Case 79 */
  if (!(toupper ('N') == 'N')) {
    failed ("Case 79: toupper ('N') == 'N'");
  }
  
  /* Case 80 */
  if (!(toupper ('O') == 'O')) {
    failed ("Case 80: toupper ('O') == 'O'");
  }
  
  /* Case 81 */
  if (!(toupper ('P') == 'P')) {
    failed ("Case 81: toupper ('P') == 'P'");
  }
  
  /* Case 82 */
  if (!(toupper ('Q') == 'Q')) {
    failed ("Case 82: toupper ('Q') == 'Q'");
  }
  
  /* Case 83 */
  if (!(toupper ('R') == 'R')) {
    failed ("Case 83: toupper ('R') == 'R'");
  }
  
  /* Case 84 */
  if (!(toupper ('S') == 'S')) {
    failed ("Case 84: toupper ('S') == 'S'");
  }
  
  /* Case 85 */
  if (!(toupper ('T') == 'T')) {
    failed ("Case 85: toupper ('T') == 'T'");
  }
  
  /* Case 86 */
  if (!(toupper ('U') == 'U')) {
    failed ("Case 86: toupper ('U') == 'U'");
  }
  
  /* Case 87 */
  if (!(toupper ('V') == 'V')) {
    failed ("Case 87: toupper ('V') == 'V'");
  }
  
  /* Case 88 */
  if (!(toupper ('W') == 'W')) {
    failed ("Case 88: toupper ('W') == 'W'");
  }
  
  /* Case 89 */
  if (!(toupper ('X') == 'X')) {
    failed ("Case 89: toupper ('X') == 'X'");
  }
  
  /* Case 90 */
  if (!(toupper ('Y') == 'Y')) {
    failed ("Case 90: toupper ('Y') == 'Y'");
  }
  
  /* Case 91 */
  if (!(toupper ('Z') == 'Z')) {
    failed ("Case 91: toupper ('Z') == 'Z'");
  }
  
  /* Case 92 */
  if (!(toupper ('[') == '[')) {
    failed ("Case 92: toupper ('[') == '['");
  }
  
  /* Case 93 */
  if (!(toupper ('\\') == '\\')) {
    failed ("Case 93: toupper ('\\\\') == '\\\\'");
  }
  
  /* Case 94 */
  if (!(toupper (']') == ']')) {
    failed ("Case 94: toupper (']') == ']'");
  }
  
  /* Case 95 */
  if (!(toupper ('^') == '^')) {
    failed ("Case 95: toupper ('^') == '^'");
  }
  
  /* Case 96 */
  if (!(toupper ('_') == '_')) {
    failed ("Case 96: toupper ('_') == '_'");
  }
  
  /* Case 97 */
  if (!(toupper ('`') == '`')) {
    failed ("Case 97: toupper ('`') == '`'");
  }
  
  /* Case 98 */
  if (!(toupper ('a') == 'A')) {
    failed ("Case 98: toupper ('a') == 'A'");
  }
  
  /* Case 99 */
  if (!(toupper ('b') == 'B')) {
    failed ("Case 99: toupper ('b') == 'B'");
  }
  
  /* Case 100 */
  if (!(toupper ('c') == 'C')) {
    failed ("Case 100: toupper ('c') == 'C'");
  }
  
  /* Case 101 */
  if (!(toupper ('d') == 'D')) {
    failed ("Case 101: toupper ('d') == 'D'");
  }
  
  /* Case 102 */
  if (!(toupper ('e') == 'E')) {
    failed ("Case 102: toupper ('e') == 'E'");
  }
  
  /* Case 103 */
  if (!(toupper ('f') == 'F')) {
    failed ("Case 103: toupper ('f') == 'F'");
  }
  
  /* Case 104 */
  if (!(toupper ('g') == 'G')) {
    failed ("Case 104: toupper ('g') == 'G'");
  }
  
  /* Case 105 */
  if (!(toupper ('h') == 'H')) {
    failed ("Case 105: toupper ('h') == 'H'");
  }
  
  /* Case 106 */
  if (!(toupper ('i') == 'I')) {
    failed ("Case 106: toupper ('i') == 'I'");
  }
  
  /* Case 107 */
  if (!(toupper ('j') == 'J')) {
    failed ("Case 107: toupper ('j') == 'J'");
  }
  
  /* Case 108 */
  if (!(toupper ('k') == 'K')) {
    failed ("Case 108: toupper ('k') == 'K'");
  }
  
  /* Case 109 */
  if (!(toupper ('l') == 'L')) {
    failed ("Case 109: toupper ('l') == 'L'");
  }
  
  /* Case 110 */
  if (!(toupper ('m') == 'M')) {
    failed ("Case 110: toupper ('m') == 'M'");
  }
  
  /* Case 111 */
  if (!(toupper ('n') == 'N')) {
    failed ("Case 111: toupper ('n') == 'N'");
  }
  
  /* Case 112 */
  if (!(toupper ('o') == 'O')) {
    failed ("Case 112: toupper ('o') == 'O'");
  }
  
  /* Case 113 */
  if (!(toupper ('p') == 'P')) {
    failed ("Case 113: toupper ('p') == 'P'");
  }
  
  /* Case 114 */
  if (!(toupper ('q') == 'Q')) {
    failed ("Case 114: toupper ('q') == 'Q'");
  }
  
  /* Case 115 */
  if (!(toupper ('r') == 'R')) {
    failed ("Case 115: toupper ('r') == 'R'");
  }
  
  /* Case 116 */
  if (!(toupper ('s') == 'S')) {
    failed ("Case 116: toupper ('s') == 'S'");
  }
  
  /* Case 117 */
  if (!(toupper ('t') == 'T')) {
    failed ("Case 117: toupper ('t') == 'T'");
  }
  
  /* Case 118 */
  if (!(toupper ('u') == 'U')) {
    failed ("Case 118: toupper ('u') == 'U'");
  }
  
  /* Case 119 */
  if (!(toupper ('v') == 'V')) {
    failed ("Case 119: toupper ('v') == 'V'");
  }
  
  /* Case 120 */
  if (!(toupper ('w') == 'W')) {
    failed ("Case 120: toupper ('w') == 'W'");
  }
  
  /* Case 121 */
  if (!(toupper ('x') == 'X')) {
    failed ("Case 121: toupper ('x') == 'X'");
  }
  
  /* Case 122 */
  if (!(toupper ('y') == 'Y')) {
    failed ("Case 122: toupper ('y') == 'Y'");
  }
  
  /* Case 123 */
  if (!(toupper ('z') == 'Z')) {
    failed ("Case 123: toupper ('z') == 'Z'");
  }
  
  /* Case 124 */
  if (!(toupper ('{') == '{')) {
    failed ("Case 124: toupper ('{') == '{'");
  }
  
  /* Case 125 */
  if (!(toupper ('|') == '|')) {
    failed ("Case 125: toupper ('|') == '|'");
  }
  
  /* Case 126 */
  if (!(toupper ('}') == '}')) {
    failed ("Case 126: toupper ('}') == '}'");
  }
  
  /* Case 127 */
  if (!(toupper ('~') == '~')) {
    failed ("Case 127: toupper ('~') == '~'");
  }
  
  /* Case 128 */
  if (!(toupper ('\177') == '\177')) {
    failed ("Case 128: toupper ('\\177') == '\\177'");
  }
  
}


void main ()
{
  test ("test-toupper", "Test for ANSI Standard C: 7.3.2.2");

  do_test ();

  result ();
}

