var rewire      = require('rewire')
var assert      = require('assert')
var should      = require("should")
var chai        = require("chai")
var ast         = require("../lib/ast")
const PEG       = require("../lib/infix2egg.js");
const inspect   = require("util").inspect;
var ins         = (x) => inspect(x, {depth:null});

describe("PEG parser", function(){
  it("should parse a simple declaration", function() {
  var program  = "var a;"
      program += "a := 1."
  var ast_tree = new ast.Apply(new ast.Word({
    value: "program",
    offset: 0,
    lineno: 1
  }),
    [ // Program args
          new ast.Apply(new ast.Word({
            value: "block",
            offset: 0,
            lineno: 1
          }),
        [ // Block args
          new ast.Apply(new ast.Word({
            value: "var",
            offset: 0,
            lineno: 1
          }),
            [ // Var args
              new ast.Word({
                value: "a",
                offset: 3,
                lineno: 1
              })
            ]),
            new ast.Apply(new ast.Word({
                value: ":=",
                offset: 6,
                lineno: 1
            }),
              [ // := args
                new ast.Word({
                  value: "a",
                  offset: 6,
                  lineno: 1
                }),
                new ast.Value({
                  value: 1,
                  offset: 10,
                  lineno: 1
                })
              ])
        ])
    ])
    ast_tree.should.be.eql(PEG.parse(program));
  })

  it("should parse a simple sum", function() {
  var program  = "var a;"
      program += "a := 1 + 2."
  var ast_tree = new ast.Apply(new ast.Word({
    value: "program",
    offset: 0,
    lineno: 1
  }),
    [ // Program args
          new ast.Apply(new ast.Word({
            value: "block",
            offset: 0,
            lineno: 1
          }),
        [ // Block args
          new ast.Apply(new ast.Word({
            value: "var",
            offset: 0,
            lineno: 1
          }),
            [ // Var args
              new ast.Word({
                value: "a",
                offset: 3,
                lineno: 1
              })
            ]),
            new ast.Apply(new ast.Word({
                value: ":=",
                offset: 6,
                lineno: 1
            }),
              [ // := args
                new ast.Word({
                  value: "a",
                  offset: 6,
                  lineno: 1
                }),
                new ast.Apply(new ast.Word({
                  value: "+",
                  offset: 13,
                  lineno: 1
                }),
                [
                  new ast.Value({
                    value: 1,
                    offset: 10,
                    lineno: 1
                  }),
                  new ast.Value({
                    value: 2,
                    offset: 14,
                    lineno: 1
                  })
                ])
              ])
        ])
    ])
    ast_tree.should.be.eql(PEG.parse(program));
  })

  it("should parse a simple product", function() {
  var program  = "var a;"
      program += "a := 1 * 2."
  var ast_tree = new ast.Apply(new ast.Word({
    value: "program",
    offset: 0,
    lineno: 1
  }),
    [ // Program args
          new ast.Apply(new ast.Word({
            value: "block",
            offset: 0,
            lineno: 1
          }),
        [ // Block args
          new ast.Apply(new ast.Word({
            value: "var",
            offset: 0,
            lineno: 1
          }),
            [ // Var args
              new ast.Word({
                value: "a",
                offset: 3,
                lineno: 1
              })
            ]),
            new ast.Apply(new ast.Word({
                value: ":=",
                offset: 6,
                lineno: 1
            }),
              [ // := args
                new ast.Word({
                  value: "a",
                  offset: 6,
                  lineno: 1
                }),
                new ast.Apply(new ast.Word({
                  value: "*",
                  offset: 13,
                  lineno: 1
                }),
                [
                  new ast.Value({
                    value: 1,
                    offset: 10,
                    lineno: 1
                  }),
                  new ast.Value({
                    value: 2,
                    offset: 14,
                    lineno: 1
                  })
                ])
              ])
        ])
    ])
    ast_tree.should.be.eql(PEG.parse(program));
  })

  it("should parse a simple arithmetic expression", function() {
  var program  = "var a;"
      program += "a := 1 * 2 + 3."
  var ast_tree = new ast.Apply(new ast.Word({
    value: "program",
    offset: 0,
    lineno: 1
  }),
    [ // Program args
          new ast.Apply(new ast.Word({
            value: "block",
            offset: 0,
            lineno: 1
          }),
        [ // Block args
          new ast.Apply(new ast.Word({
            value: "var",
            offset: 0,
            lineno: 1
          }),
            [ // Var args
              new ast.Word({
                value: "a",
                offset: 3,
                lineno: 1
              })
            ]),
            new ast.Apply(new ast.Word({
                value: ":=",
                offset: 6,
                lineno: 1
            }),
              [ // := args
                new ast.Word({
                  value: "a",
                  offset: 6,
                  lineno: 1
                }),
                new ast.Apply(new ast.Word({
                  value: "+",
                  offset: 17,
                  lineno: 1
                }),
                [
                  new ast.Apply(new ast.Word({
                    value: "*",
                    offset: 13,
                    lineno: 1
                  }),
                  [
                    new ast.Value({
                      value: 1,
                      offset: 10,
                      lineno: 1
                    }),
                    new ast.Value({
                      value: 2,
                      offset: 14,
                      lineno: 1
                    })
                  ]),
                  new ast.Value({
                    value: 3,
                    offset: 18,
                    lineno: 1
                  })
                ])
              ])
        ])
    ])
    ast_tree.should.be.eql(PEG.parse(program));
  })

  it("should parse an arithmetic expression with parenthesis", function() {
  var program  = "var a;"
      program += "a := 1 * (2 + 3)."
  var ast_tree = new ast.Apply(new ast.Word({
    value: "program",
    offset: 0,
    lineno: 1
  }),
    [ // Program args
          new ast.Apply(new ast.Word({
            value: "block",
            offset: 0,
            lineno: 1
          }),
        [ // Block args
          new ast.Apply(new ast.Word({
            value: "var",
            offset: 0,
            lineno: 1
          }),
            [ // Var args
              new ast.Word({
                value: "a",
                offset: 3,
                lineno: 1
              })
            ]),
            new ast.Apply(new ast.Word({
                value: ":=",
                offset: 6,
                lineno: 1
            }),
              [ // := args
                new ast.Word({
                  value: "a",
                  offset: 6,
                  lineno: 1
                }),
                new ast.Apply(new ast.Word({
                  value: "*",
                  offset: 13,
                  lineno: 1
                }),
                [
                  new ast.Value({
                    value: 1,
                    offset: 10,
                    lineno: 1
                  }),
                  new ast.Apply(new ast.Word({
                    value: "+",
                    offset: 18,
                    lineno: 1
                  }),
                  [
                    new ast.Value({
                      value: 2,
                      offset: 16,
                      lineno: 1
                    }),
                    new ast.Value({
                      value: 3,
                      offset: 19,
                      lineno: 1
                    })
                  ])
                ])
              ])
        ])
    ])
    ast_tree.should.be.eql(PEG.parse(program));
  })

  it("should parse an if statement", function() {
  var program   = "if a < 2 then a:= 1 + 3 else b:= 1 + 4."
  var ast_tree = new ast.Apply(new ast.Word({
    value: "program",
    offset: 0,
    lineno: 1
  }),
  [
    new ast.Apply(new ast.Word({
      value: "block",
      offset: 0,
      lineno: 1
    }),
      [
        new ast.Apply(new ast.Word({
          value: "if",
          offset: 0,
          lineno: 1,
        }),
          [
            new ast.Apply(new ast.Word({
              value: "<",
              offset: 2,
              lineno: 1
            }),
              [
                new ast.Word({
                  value: "a",
                  offset: 2,
                  lineno: 1
                }),
                new ast.Value({
                  value: 2,
                  offset: 6,
                  lineno: 1
                })
              ]),
              new ast.Apply(new ast.Word({
                value: ":=",
                offset: 14,
                lineno: 1
              }),
                [
                  new ast.Word({
                    value: "a",
                    offset: 14,
                    lineno: 1
                  }),
                  new ast.Apply(new ast.Word({
                    value: "+",
                    offset: 20,
                    lineno: 1
                  }),
                    [
                      new ast.Value({
                        value: 1,
                        offset: 17,
                        lineno: 1
                      }),
                      new ast.Value({
                        value: 3,
                        offset: 21,
                        lineno: 1
                      })
                    ])
                ]),
                new ast.Apply(new ast.Word({
                  value: ":=",
                  offset: 29,
                  lineno: 1
                }),
                  [
                    new ast.Word({
                      value: "b",
                      offset: 29,
                      lineno: 1
                    }),
                    new ast.Apply(new ast.Word({
                      value: "+",
                      offset: 35,
                      lineno: 1
                    }),
                      [
                        new ast.Value({
                          value: 1,
                          offset: 32,
                          lineno: 1
                        }),
                        new ast.Value({
                          value: 4,
                          offset: 36,
                          lineno: 1
                        })
                      ])
                  ])
          ])
      ])
  ])

    ast_tree.should.be.eql(PEG.parse(program));
  })

  it("should parse a print", function() {
  var program  = "print(1)."
  var ast_tree = new ast.Apply(new ast.Word({
    value: "program",
    offset: 0,
    lineno: 1
  }),
    [ // Program args
          new ast.Apply(new ast.Word({
            value: "block",
            offset: 0,
            lineno: 1
          }),
            [
              new ast.Apply(new ast.Word({
                value: "print",
                offset: 0,
                lineno: 1
              }),
                [
                  new ast.Value({
                    value: 1,
                    offset: 6,
                    lineno: 1
                  })
                ])
            ])
    ])
    ast_tree.should.be.eql(PEG.parse(program));
  })

  it("should parse a while", function() {
  var program  = "while a < 2 do b := 1."
  var ast_tree = new ast.Apply(new ast.Word({
    value: "program",
    offset: 0,
    lineno: 1
  }),
    [ // Program args
          new ast.Apply(new ast.Word({
            value: "block",
            offset: 0,
            lineno: 1
          }),
            [
              new ast.Apply(new ast.Word({
                value: "while",
                offset: 0,
                lineno: 1
              }),
                [
                  new ast.Apply(new ast.Word({
                    value: "<",
                    offset: 5,
                    lineno: 1
                  }),
                    [
                      new ast.Word({
                        value: "a",
                        offset: 5,
                        lineno: 1
                      }),
                      new ast.Value({
                        value: 2,
                        offset: 9,
                        lineno: 1
                      })
                    ]),
                    new ast.Apply(new ast.Word({
                      value: ":=",
                      offset: 15,
                      lineno: 1
                    }),
                      [
                        new ast.Word({
                          value: "b",
                          offset: 15,
                          lineno: 1
                        }),
                        new ast.Value({
                          value: 1,
                          offset: 19,
                          lineno: 1
                        }),
                      ])
                ])
            ])
    ])
    ast_tree.should.be.eql(PEG.parse(program));
  })

  it("should parse a begin end", function() {
  var program  = "begin	a := 1; b := 2 end."
  var ast_tree = new ast.Apply(new ast.Word({
    value: "program",
    offset: 0,
    lineno: 1
  }),
    [ // Program args
          new ast.Apply(new ast.Word({
            value: "block",
            offset: 0,
            lineno: 1
          }),
            [
              new ast.Apply(new ast.Word({
                value: "do",
                offset: 0,
                lineno: 1
              }),
                [
                  new ast.Apply(new ast.Word({
                    value: ":=",
                    offset: 6,
                    lineno: 1
                  }),
                    [
                      new ast.Word({
                        value: "a",
                        offset: 6,
                        lineno: 1
                      }),
                      new ast.Value({
                        value: 1,
                        offset: 10,
                        lineno: 1
                      }),
                    ]),
                    new ast.Apply(new ast.Word({
                      value: ":=",
                      offset: 14,
                      lineno: 1
                    }),
                      [
                        new ast.Word({
                          value: "b",
                          offset: 14,
                          lineno: 1
                        }),
                        new ast.Value({
                          value: 2,
                          offset: 18,
                          lineno: 1
                        }),
                      ])
                ])
            ])
    ])
    ast_tree.should.be.eql(PEG.parse(program));
  })

  it("should parse a print", function() {
  var program  = "call a."
  var ast_tree = new ast.Apply(new ast.Word({
    value: "program",
    offset: 0,
    lineno: 1
  }),
    [ // Program args
          new ast.Apply(new ast.Word({
            value: "block",
            offset: 0,
            lineno: 1
          }),
            [
              new ast.Apply(new ast.Word({
                value: "call",
                offset: 0,
                lineno: 1
              }),
                [
                  new ast.Word({
                    value: "a",
                    offset: 4,
                    lineno: 1
                  })
                ])
            ])
    ])
    ast_tree.should.be.eql(PEG.parse(program));
  })

  it("should parse a procedure", function(){
    var program = "procedure primes;a := 1;call primes."
    var ast_tree = new ast.Apply(new ast.Word({
      value: "program",
      offset: 0,
      lineno: 1
    }),
      [ // Program args
            new ast.Apply(new ast.Word({
              value: "block",
              offset: 0,
              lineno: 1
            }),
              [
                new ast.Apply(new ast.Word({
                  value: "def",
                  offset: 0,
                  lineno: 1
                }),
                  [
                    new ast.Word({
                      value: "primes",
                      offset: 9,
                      lineno: 1
                    }),
                    new ast.Apply(new ast.Word(
                      {
                        value: "block",
                        offset: 17,
                        lineno: 1
                      }
                    ),
                      [
                        new ast.Apply(new ast.Word(
                          {
                            value: ":=",
                            offset: 17,
                            lineno: 1
                          }
                        ),[
                          new ast.Word({
                            value: "a",
                            offset: 17,
                            lineno: 1
                          }),
                          new ast.Value({
                            value: 1,
                            offset: 21,
                            lineno: 1
                          })
                        ])
                      ])
                  ]),
                  new ast.Apply(new ast.Word(
                    {
                      value: "call",
                      offset: 24,
                      lineno: 1
                    }
                  ),
                  [
                    new ast.Word(
                      {
                        value: "primes",
                        offset: 28,
                        lineno: 1
                      }
                    )
                  ])
              ])
      ])
      ast_tree.should.be.eql(PEG.parse(program));

  })

});
