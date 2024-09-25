# clang-format

*clang-format* is a tool to format C/C++/... code according to a set of rules and heuristics. Like most tools, it is not perfect nor covers every single case, but it is good enough to be helpful.

See more information about the tool at:

    https://clang.llvm.org/docs/ClangFormat.html

    https://clang.llvm.org/docs/ClangFormatStyleOptions.html

## Review files and patches for coding style

By running the tool in its inline mode, you can review full subsystems, folders or individual files for code style mistakes, typos or improvements.

To do so, you can run something like:

```bash
# Make sure your working directory is clean!
clang-format -i kernel/*.[ch]
```

## Reformatting blocks of code

By using an integration with your text editor, you can reformat arbitrary blocks (selections) of code with a single keystroke. This is specially useful when moving code around, for complex code that is deeply intended, for multi-line macros (and aligning their backslashes), etc.

Remember that you can always tweak the changes afterwards in those cases where the tool did not do an optimal job. But as a first approximation, it can be very useful.

There are integrations for many popular text editors. For some of them, like vim, emacs, BBEdit and Visual Studio you can find support built-in. For instructions, read the appropriate section at:

    https://clang.llvm.org/docs/ClangFormat.html

### Source

    https://docs.kernel.org/dev-tools/clang-format.html
