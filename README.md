A nonogram solver that can solve [nonograms](https://en.wikipedia.org/wiki/Nonogram) with m columns and n rows as long as m + n <= 80.

## How to input puzzles
- First input: an integer m representing the number of columns.
- Second input: an integer n representing the number of rows.
- Third input: a string without spaces representing the hints.

## Format of the string
```
col_0_hint + "," + col_1_hint + "," ... col_(m-1)_hint + "," + row_0_hint + "," + row_1_hint + "," ... row_(n-1)_hint
```

Consider if the hints for column 0 were `1, 3, 16`. In this case, `column_0_hint` would be `13G`, where numbers exceeding 9 are denoted using English alphabets.

For example, the following puzzle:

```
┌───╥───┬───┬───┐
│   ║   │ 1 │   │
│   ║ 1 │ 1 │   │
╞═══╬═══╪═══╪═══╡
│ 2 ║ █ │ █ │   │
├───╫───┼───┼───┤
│   ║   │   │   │
├───╫───┼───┼───┤
│ 1 ║   │ █ │   │
└───╨───┴───┴───┘
```

can be inputted with the string `1,11,,2,,1`.