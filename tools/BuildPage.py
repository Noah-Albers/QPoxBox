#!/usr/bin/env python3

import os
import re

# Read the input file
with open('../index.html', 'r', encoding='utf-8') as infile:
    content = infile.read()

# Replace every newline followed by whitespace with a single space
modified_content = re.sub(r'\n\s*', ' ', content)

# Create a header file with the content as a string
with open('../tmp_index_html.h', 'w', encoding='utf-8') as outfile:
    outfile.write('#ifndef INDEX_HTML_H\n')
    outfile.write('#define INDEX_HTML_H\n\n')
    outfile.write('const char* index_html = R"rawliteral(\n')
    outfile.write(modified_content)
    outfile.write(')rawliteral";\n\n')
    outfile.write('#endif // INDEX_HTML_H\n')

print("Processing complete. Output written to index_html.h")
