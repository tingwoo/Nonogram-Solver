A nonogram solver that can solve [nonograms](https://en.wikipedia.org/wiki/Nonogram) with m columns and n rows as long as m + n <= 80.

## How to input puzzles
- First input: an integer **m** representing the number of columns.
- Second input: an integer **n** representing the number of rows.
- Third input: a string without spaces representing the hints.

## Format of the string

```
col_0_hint + "," + col_1_hint + "," ... col_(m-1)_hint + "," + row_0_hint + "," + row_1_hint + "," ... row_(n-1)_hint
```

If the hints for column 0 are `1, 3, 16, 10`, `column_0_hint` would be `13GA`, where numbers exceeding 9 are denoted using English alphabets.

For example, the following puzzle:

```
┌─────╥───┬───┬───┬───┐
│     ║   │ 1 │   │   │
│     ║ 1 │ 2 │ 1 │ 2 │
╞═════╬═══╪═══╪═══╪═══╡
│   2 ║ █ │ █ │   │   │
├─────╫───┼───┼───┼───┤
│     ║   │   │   │   │
├─────╫───┼───┼───┼───┤
│   3 ║   │ █ │ █ │ █ │
├─────╫───┼───┼───┼───┤
│ 1 1 ║   │ █ │   │ █ │
└─────╨───┴───┴───┴───┘
```

can be represented with the string `1,12,1,2,2,,3,11`.

## Example

Once compiled, you can test the solver with the following input:
```
30 35
5EA,574112,G3111,245411,23131221,631131,63541,2251221,1242121,511124221,61511212121,721211144,72212122,72114,633112,631111,113311,63131,63221,A321,4231,651221,733132,721311,15A211,1E1312,D2283,566224,5E1215,872225,798,67334,328334,32839,8739,8B61,54151,2586,15D5,4J4,5235,611117,513316,4111122,39122,41517,121118,1215423,444212,338215,3412244,2152521,11C5,131,1212,1123,1421,1212,11,1212,21213,11414,22225,3346,33
```