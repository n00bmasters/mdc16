asect 0x00
code_start: ext
rsect test
code_start>
# load string length into r0
halt

string_start:
dc "Hello, wr5yrh5orld", 0x0a, 0x00
string_stop:


end