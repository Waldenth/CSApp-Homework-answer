Disassembly of section .text:

0000000000000000 <main>:
   0:   48 83 ec 28             sub    $0x28,%rsp
   4:   e8 00 00 00 00          callq  9 <main+0x9>
                        5: R_X86_64_PC32        __main
   9:   ba 02 00 00 00          mov    $0x2,%edx
   e:   48 8d 0d 00 00 00 00    lea    0x0(%rip),%rcx        # 15 <main+0x15>
                        11: R_X86_64_PC32       .data
  15:   e8 00 00 00 00          callq  1a <main+0x1a>
                        16: R_X86_64_PC32       sum
  1a:   48 83 c4 28             add    $0x28,%rsp
  1e:   c3                      retq
  1f:   90                      nop