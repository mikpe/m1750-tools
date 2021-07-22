/*
 * Test for ANSI Standard C: 7.3.2.1
 * 
 * #include <ctype.h>
 * int tolower (int c);
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


static char *_test_tolower_id =
  "$Id$";

void do_test ()
{
  /* Case 1 */
  if (!(tolower ('\000') == '\000')) {
    failed ("Case 1: tolower ('\\000') == '\\000'");
  }
  
  /* Case 2 */
  if (!(tolower ('\001') == '\001')) {
    failed ("Case 2: tolower ('\\001') == '\\001'");
  }
  
  /* Case 3 */
  if (!(tolower ('\002') == '\002')) {
    failed ("Case 3: tolower ('\\002') == '\\002'");
  }
  
  /* Case 4 */
  if (!(tolower ('\003') == '\003')) {
    failed ("Case 4: tolower ('\\003') == '\\003'");
  }
  
  /* Case 5 */
  if (!(tolower ('\004') == '\004')) {
    failed ("Case 5: tolower ('\\004') == '\\004'");
  }
  
  /* Case 6 */
  if (!(tolower ('\005') == '\005')) {
    failed ("Case 6: tolower ('\\005') == '\\005'");
  }
  
  /* Case 7 */
  if (!(tolower ('\006') == '\006')) {
    failed ("Case 7: tolower ('\\006') == '\\006'");
  }
  
  /* Case 8 */
  if (!(tolower ('\007') == '\007')) {
    failed ("Case 8: tolower ('\\007') == '\\007'");
  }
  
  /* Case 9 */
  if (!(tolower ('\010') == '\010')) {
    failed ("Case 9: tolower ('\\010') == '\\010'");
  }
  
  /* Case 10 */
  if (!(tolower ('\011') == '\011')) {
    failed ("Case 10: tolower ('\\011') == '\\011'");
  }
  
  /* Case 11 */
  if (!(tolower ('\012') == '\012')) {
    failed ("Case 11: tolower ('\\012') == '\\012'");
  }
  
  /* Case 12 */
  if (!(tolower ('\013') == '\013')) {
    failed ("Case 12: tolower ('\\013') == '\\013'");
  }
  
  /* Case 13 */
  if (!(tolower ('\014') == '\014')) {
    failed ("Case 13: tolower ('\\014') == '\\014'");
  }
  
  /* Case 14 */
  if (!(tolower ('\015') == '\015')) {
    failed ("Case 14: tolower ('\\015') == '\\015'");
  }
  
  /* Case 15 */
  if (!(tolower ('\016') == '\016')) {
    failed ("Case 15: tolower ('\\016') == '\\016'");
  }
  
  /* Case 16 */
  if (!(tolower ('\017') == '\017')) {
    failed ("Case 16: tolower ('\\017') == '\\017'");
  }
  
  /* Case 17 */
  if (!(tolower ('\020') == '\020')) {
    failed ("Case 17: tolower ('\\020') == '\\020'");
  }
  
  /* Case 18 */
  if (!(tolower ('\021') == '\021')) {
    failed ("Case 18: tolower ('\\021') == '\\021'");
  }
  
  /* Case 19 */
  if (!(tolower ('\022') == '\022')) {
    failed ("Case 19: tolower ('\\022') == '\\022'");
  }
  
  /* Case 20 */
  if (!(tolower ('\023') == '\023')) {
    failed ("Case 20: tolower ('\\023') == '\\023'");
  }
  
  /* Case 21 */
  if (!(tolower ('\024') == '\024')) {
    failed ("Case 21: tolower ('\\024') == '\\024'");
  }
  
  /* Case 22 */
  if (!(tolower ('\025') == '\025')) {
    failed ("Case 22: tolower ('\\025') == '\\025'");
  }
  
  /* Case 23 */
  if (!(tolower ('\026') == '\026')) {
    failed ("Case 23: tolower ('\\026') == '\\026'");
  }
  
  /* Case 24 */
  if (!(tolower ('\027') == '\027')) {
    failed ("Case 24: tolower ('\\027') == '\\027'");
  }
  
  /* Case 25 */
  if (!(tolower ('\030') == '\030')) {
    failed ("Case 25: tolower ('\\030') == '\\030'");
  }
  
  /* Case 26 */
  if (!(tolower ('\031') == '\031')) {
    failed ("Case 26: tolower ('\\031') == '\\031'");
  }
  
  /* Case 27 */
  if (!(tolower ('\032') == '\032')) {
    failed ("Case 27: tolower ('\\032') == '\\032'");
  }
  
  /* Case 28 */
  if (!(tolower ('\033') == '\033')) {
    failed ("Case 28: tolower ('\\033') == '\\033'");
  }
  
  /* Case 29 */
  if (!(tolower ('\034') == '\034')) {
    failed ("Case 29: tolower ('\\034') == '\\034'");
  }
  
  /* Case 30 */
  if (!(tolower ('\035') == '\035')) {
    failed ("Case 30: tolower ('\\035') == '\\035'");
  }
  
  /* Case 31 */
  if (!(tolower ('\036') == '\036')) {
    failed ("Case 31: tolower ('\\036') == '\\036'");
  }
  
  /* Case 32 */
  if (!(tolower ('\037') == '\037')) {
    failed ("Case 32: tolower ('\\037') == '\\037'");
  }
  
  /* Case 33 */
  if (!(tolower (' ') == ' ')) {
    failed ("Case 33: tolower (' ') == ' '");
  }
  
  /* Case 34 */
  if (!(tolower ('!') == '!')) {
    failed ("Case 34: tolower ('!') == '!'");
  }
  
  /* Case 35 */
  if (!(tolower ('\"') == '\"')) {
    failed ("Case 35: tolower ('\\\"') == '\\\"'");
  }
  
  /* Case 36 */
  if (!(tolower ('#') == '#')) {
    failed ("Case 36: tolower ('#') == '#'");
  }
  
  /* Case 37 */
  if (!(tolower ('$') == '$')) {
    failed ("Case 37: tolower ('$') == '$'");
  }
  
  /* Case 38 */
  if (!(tolower ('%') == '%')) {
    failed ("Case 38: tolower ('%') == '%'");
  }
  
  /* Case 39 */
  if (!(tolower ('&') == '&')) {
    failed ("Case 39: tolower ('&') == '&'");
  }
  
  /* Case 40 */
  if (!(tolower ('\'') == '\'')) {
    failed ("Case 40: tolower ('\\'') == '\\''");
  }
  
  /* Case 41 */
  if (!(tolower ('(') == '(')) {
    failed ("Case 41: tolower ('(') == '('");
  }
  
  /* Case 42 */
  if (!(tolower (')') == ')')) {
    failed ("Case 42: tolower (')') == ')'");
  }
  
  /* Case 43 */
  if (!(tolower ('*') == '*')) {
    failed ("Case 43: tolower ('*') == '*'");
  }
  
  /* Case 44 */
  if (!(tolower ('+') == '+')) {
    failed ("Case 44: tolower ('+') == '+'");
  }
  
  /* Case 45 */
  if (!(tolower (',') == ',')) {
    failed ("Case 45: tolower (',') == ','");
  }
  
  /* Case 46 */
  if (!(tolower ('-') == '-')) {
    failed ("Case 46: tolower ('-') == '-'");
  }
  
  /* Case 47 */
  if (!(tolower ('.') == '.')) {
    failed ("Case 47: tolower ('.') == '.'");
  }
  
  /* Case 48 */
  if (!(tolower ('/') == '/')) {
    failed ("Case 48: tolower ('/') == '/'");
  }
  
  /* Case 49 */
  if (!(tolower ('0') == '0')) {
    failed ("Case 49: tolower ('0') == '0'");
  }
  
  /* Case 50 */
  if (!(tolower ('1') == '1')) {
    failed ("Case 50: tolower ('1') == '1'");
  }
  
  /* Case 51 */
  if (!(tolower ('2') == '2')) {
    failed ("Case 51: tolower ('2') == '2'");
  }
  
  /* Case 52 */
  if (!(tolower ('3') == '3')) {
    failed ("Case 52: tolower ('3') == '3'");
  }
  
  /* Case 53 */
  if (!(tolower ('4') == '4')) {
    failed ("Case 53: tolower ('4') == '4'");
  }
  
  /* Case 54 */
  if (!(tolower ('5') == '5')) {
    failed ("Case 54: tolower ('5') == '5'");
  }
  
  /* Case 55 */
  if (!(tolower ('6') == '6')) {
    failed ("Case 55: tolower ('6') == '6'");
  }
  
  /* Case 56 */
  if (!(tolower ('7') == '7')) {
    failed ("Case 56: tolower ('7') == '7'");
  }
  
  /* Case 57 */
  if (!(tolower ('8') == '8')) {
    failed ("Case 57: tolower ('8') == '8'");
  }
  
  /* Case 58 */
  if (!(tolower ('9') == '9')) {
    failed ("Case 58: tolower ('9') == '9'");
  }
  
  /* Case 59 */
  if (!(tolower (':') == ':')) {
    failed ("Case 59: tolower (':') == ':'");
  }
  
  /* Case 60 */
  if (!(tolower (';') == ';')) {
    failed ("Case 60: tolower (';') == ';'");
  }
  
  /* Case 61 */
  if (!(tolower ('<') == '<')) {
    failed ("Case 61: tolower ('<') == '<'");
  }
  
  /* Case 62 */
  if (!(tolower ('=') == '=')) {
    failed ("Case 62: tolower ('=') == '='");
  }
  
  /* Case 63 */
  if (!(tolower ('>') == '>')) {
    failed ("Case 63: tolower ('>') == '>'");
  }
  
  /* Case 64 */
  if (!(tolower ('?') == '?')) {
    failed ("Case 64: tolower ('?') == '?'");
  }
  
  /* Case 65 */
  if (!(tolower ('@') == '@')) {
    failed ("Case 65: tolower ('@') == '@'");
  }
  
  /* Case 66 */
  if (!(tolower ('A') == 'a')) {
    failed ("Case 66: tolower ('A') == 'a'");
  }
  
  /* Case 67 */
  if (!(tolower ('B') == 'b')) {
    failed ("Case 67: tolower ('B') == 'b'");
  }
  
  /* Case 68 */
  if (!(tolower ('C') == 'c')) {
    failed ("Case 68: tolower ('C') == 'c'");
  }
  
  /* Case 69 */
  if (!(tolower ('D') == 'd')) {
    failed ("Case 69: tolower ('D') == 'd'");
  }
  
  /* Case 70 */
  if (!(tolower ('E') == 'e')) {
    failed ("Case 70: tolower ('E') == 'e'");
  }
  
  /* Case 71 */
  if (!(tolower ('F') == 'f')) {
    failed ("Case 71: tolower ('F') == 'f'");
  }
  
  /* Case 72 */
  if (!(tolower ('G') == 'g')) {
    failed ("Case 72: tolower ('G') == 'g'");
  }
  
  /* Case 73 */
  if (!(tolower ('H') == 'h')) {
    failed ("Case 73: tolower ('H') == 'h'");
  }
  
  /* Case 74 */
  if (!(tolower ('I') == 'i')) {
    failed ("Case 74: tolower ('I') == 'i'");
  }
  
  /* Case 75 */
  if (!(tolower ('J') == 'j')) {
    failed ("Case 75: tolower ('J') == 'j'");
  }
  
  /* Case 76 */
  if (!(tolower ('K') == 'k')) {
    failed ("Case 76: tolower ('K') == 'k'");
  }
  
  /* Case 77 */
  if (!(tolower ('L') == 'l')) {
    failed ("Case 77: tolower ('L') == 'l'");
  }
  
  /* Case 78 */
  if (!(tolower ('M') == 'm')) {
    failed ("Case 78: tolower ('M') == 'm'");
  }
  
  /* Case 79 */
  if (!(tolower ('N') == 'n')) {
    failed ("Case 79: tolower ('N') == 'n'");
  }
  
  /* Case 80 */
  if (!(tolower ('O') == 'o')) {
    failed ("Case 80: tolower ('O') == 'o'");
  }
  
  /* Case 81 */
  if (!(tolower ('P') == 'p')) {
    failed ("Case 81: tolower ('P') == 'p'");
  }
  
  /* Case 82 */
  if (!(tolower ('Q') == 'q')) {
    failed ("Case 82: tolower ('Q') == 'q'");
  }
  
  /* Case 83 */
  if (!(tolower ('R') == 'r')) {
    failed ("Case 83: tolower ('R') == 'r'");
  }
  
  /* Case 84 */
  if (!(tolower ('S') == 's')) {
    failed ("Case 84: tolower ('S') == 's'");
  }
  
  /* Case 85 */
  if (!(tolower ('T') == 't')) {
    failed ("Case 85: tolower ('T') == 't'");
  }
  
  /* Case 86 */
  if (!(tolower ('U') == 'u')) {
    failed ("Case 86: tolower ('U') == 'u'");
  }
  
  /* Case 87 */
  if (!(tolower ('V') == 'v')) {
    failed ("Case 87: tolower ('V') == 'v'");
  }
  
  /* Case 88 */
  if (!(tolower ('W') == 'w')) {
    failed ("Case 88: tolower ('W') == 'w'");
  }
  
  /* Case 89 */
  if (!(tolower ('X') == 'x')) {
    failed ("Case 89: tolower ('X') == 'x'");
  }
  
  /* Case 90 */
  if (!(tolower ('Y') == 'y')) {
    failed ("Case 90: tolower ('Y') == 'y'");
  }
  
  /* Case 91 */
  if (!(tolower ('Z') == 'z')) {
    failed ("Case 91: tolower ('Z') == 'z'");
  }
  
  /* Case 92 */
  if (!(tolower ('[') == '[')) {
    failed ("Case 92: tolower ('[') == '['");
  }
  
  /* Case 93 */
  if (!(tolower ('\\') == '\\')) {
    failed ("Case 93: tolower ('\\\\') == '\\\\'");
  }
  
  /* Case 94 */
  if (!(tolower (']') == ']')) {
    failed ("Case 94: tolower (']') == ']'");
  }
  
  /* Case 95 */
  if (!(tolower ('^') == '^')) {
    failed ("Case 95: tolower ('^') == '^'");
  }
  
  /* Case 96 */
  if (!(tolower ('_') == '_')) {
    failed ("Case 96: tolower ('_') == '_'");
  }
  
  /* Case 97 */
  if (!(tolower ('`') == '`')) {
    failed ("Case 97: tolower ('`') == '`'");
  }
  
  /* Case 98 */
  if (!(tolower ('a') == 'a')) {
    failed ("Case 98: tolower ('a') == 'a'");
  }
  
  /* Case 99 */
  if (!(tolower ('b') == 'b')) {
    failed ("Case 99: tolower ('b') == 'b'");
  }
  
  /* Case 100 */
  if (!(tolower ('c') == 'c')) {
    failed ("Case 100: tolower ('c') == 'c'");
  }
  
  /* Case 101 */
  if (!(tolower ('d') == 'd')) {
    failed ("Case 101: tolower ('d') == 'd'");
  }
  
  /* Case 102 */
  if (!(tolower ('e') == 'e')) {
    failed ("Case 102: tolower ('e') == 'e'");
  }
  
  /* Case 103 */
  if (!(tolower ('f') == 'f')) {
    failed ("Case 103: tolower ('f') == 'f'");
  }
  
  /* Case 104 */
  if (!(tolower ('g') == 'g')) {
    failed ("Case 104: tolower ('g') == 'g'");
  }
  
  /* Case 105 */
  if (!(tolower ('h') == 'h')) {
    failed ("Case 105: tolower ('h') == 'h'");
  }
  
  /* Case 106 */
  if (!(tolower ('i') == 'i')) {
    failed ("Case 106: tolower ('i') == 'i'");
  }
  
  /* Case 107 */
  if (!(tolower ('j') == 'j')) {
    failed ("Case 107: tolower ('j') == 'j'");
  }
  
  /* Case 108 */
  if (!(tolower ('k') == 'k')) {
    failed ("Case 108: tolower ('k') == 'k'");
  }
  
  /* Case 109 */
  if (!(tolower ('l') == 'l')) {
    failed ("Case 109: tolower ('l') == 'l'");
  }
  
  /* Case 110 */
  if (!(tolower ('m') == 'm')) {
    failed ("Case 110: tolower ('m') == 'm'");
  }
  
  /* Case 111 */
  if (!(tolower ('n') == 'n')) {
    failed ("Case 111: tolower ('n') == 'n'");
  }
  
  /* Case 112 */
  if (!(tolower ('o') == 'o')) {
    failed ("Case 112: tolower ('o') == 'o'");
  }
  
  /* Case 113 */
  if (!(tolower ('p') == 'p')) {
    failed ("Case 113: tolower ('p') == 'p'");
  }
  
  /* Case 114 */
  if (!(tolower ('q') == 'q')) {
    failed ("Case 114: tolower ('q') == 'q'");
  }
  
  /* Case 115 */
  if (!(tolower ('r') == 'r')) {
    failed ("Case 115: tolower ('r') == 'r'");
  }
  
  /* Case 116 */
  if (!(tolower ('s') == 's')) {
    failed ("Case 116: tolower ('s') == 's'");
  }
  
  /* Case 117 */
  if (!(tolower ('t') == 't')) {
    failed ("Case 117: tolower ('t') == 't'");
  }
  
  /* Case 118 */
  if (!(tolower ('u') == 'u')) {
    failed ("Case 118: tolower ('u') == 'u'");
  }
  
  /* Case 119 */
  if (!(tolower ('v') == 'v')) {
    failed ("Case 119: tolower ('v') == 'v'");
  }
  
  /* Case 120 */
  if (!(tolower ('w') == 'w')) {
    failed ("Case 120: tolower ('w') == 'w'");
  }
  
  /* Case 121 */
  if (!(tolower ('x') == 'x')) {
    failed ("Case 121: tolower ('x') == 'x'");
  }
  
  /* Case 122 */
  if (!(tolower ('y') == 'y')) {
    failed ("Case 122: tolower ('y') == 'y'");
  }
  
  /* Case 123 */
  if (!(tolower ('z') == 'z')) {
    failed ("Case 123: tolower ('z') == 'z'");
  }
  
  /* Case 124 */
  if (!(tolower ('{') == '{')) {
    failed ("Case 124: tolower ('{') == '{'");
  }
  
  /* Case 125 */
  if (!(tolower ('|') == '|')) {
    failed ("Case 125: tolower ('|') == '|'");
  }
  
  /* Case 126 */
  if (!(tolower ('}') == '}')) {
    failed ("Case 126: tolower ('}') == '}'");
  }
  
  /* Case 127 */
  if (!(tolower ('~') == '~')) {
    failed ("Case 127: tolower ('~') == '~'");
  }
  
  /* Case 128 */
  if (!(tolower ('\177') == '\177')) {
    failed ("Case 128: tolower ('\\177') == '\\177'");
  }
  
}


void main ()
{
  test ("test-tolower", "Test for ANSI Standard C: 7.3.2.1");

  do_test ();

  result ();
}

