#include "parser/c.tab.h"
#include "parser/c.yy.h"

#include <cstdio>

//
// Main entry point
//
int main(int argc, char** argv) {

  if (argc < 2) {
    fprintf(stderr, "scc: Error! No input file given!\n");
    fprintf(stderr, "Usage: %s <infile> [outfile]\n", argv[0]);
    return 3;
  }

  // Open the file for reading
  FILE* file = fopen(argv[1], "r");
  if (file == NULL) {
    fprintf(stderr, "Error opening file '%s'!\n", argv[1]);
    return 1;
  }

  // Get everything ready to parse
  yyscan_t scanner;
  cclex_init(&scanner);
  ccset_in(file, scanner);

  int result = ccparse(scanner);

  cclex_destroy(scanner);
  fclose(file);

  // if (result != 0) { return delete (program), 1; }

  // Output the program to the file
  // string outfile = argv[1];
  // if (argc > 2) {outfile = argv[2];} else {outfile += ".c";}
  // if (!program->toProgram(outfile.c_str())) {
  // 	return delete(program),2;
  // }
  // delete program;

  return 0;
}
