# myscheme
A Scheme Interpreter Using C++

###词法规则：

`Token`	　　　　　	　　　　　	　——> `Identifer` | `Number` | `Boolean` | `String` | `(` | `)` | `.`<br>
`Identifer`	　　　　　	　　　　　——> `Inital` `Subsequent*` | `PeculiarIdentifer`<br>
`Delimiter`			　　　　　——> `Space` | `Newline` | `(` | `)` | `"` | `;`<br>
`PeculiarIdentifer`		　——> `+` | `-`<br>
`Inital` 			　　　　　——> `Letter` | `SpecialInital`<br>
`Letter` 			　　　　　——> `[a-zA-Z]`<br>
`SpecialInital` 	——> `!` | `$` | `&` | `*` | `/` | `:` | `<` | `=` | `>` | `?` | `^` | `_`<br>
`Subsequent`		——> `Inital` | `Digit` | `SpecialSubsequent`<br>
`SpecialSubsequent`	——> `+` | `-` | `.`<br>
`Number`		——> `[Sign]` `Digit` `Digit*`<br>
`Sign`			——> `+` | `-`<br>
`Digit` 		——> `[0-9]`<br>
`Boolean`		——> `#t`|`#f`<br>
`String` 		——> `" StringElement* "`<br>
`StringElement` 	——> `any other character except " and \\`<br>
`Comment` 		——> `; all subsquent characters up to line break`<br>
`keyword`   		——> `quote` | `lambda` | `if` | `set!` | `begin` | `cond` | `and` | `or` | `case` | `let` | `delay`

###文法规则：
 `Expression` 		——> `Variable`<br>
	　　　　　| `Literal`<br>
	　　　　　| `ProcedureCall`<br>
	　　　　　| `LambdaExpression`<br>
	　　　　　| `Conditional`<br>
	　　　　　| `Assignment`<br>

`Literal` 		——> `Self-evaluating` | `Quotation`<br>
`Self-evaluating`	——> `Number` | `Boolean` | `String`<br>
`ProcedureCall`		——> `(Operator Operand*)`<br>
`Operator`		——> `Expression`<br>
`Operand`		——> `Expression`<br>
`LambdaExpression`     ——> `(lambda Formals Body)`<br>
`Formals`		——> `(Variable*)` <br>
	　　　　　| `Variable`<br>
	　　　　　| `(Variable+ . Variable)`<br>

`Body`			——> `Definition*` `Sequence`<br>
`Sequence`		——> `Command*` `Expression`<br>
`Command`		——> `Expression`<br>
`Conditional`		——> `(if Test Consqeuence Alternate)`<br>
`Test`			——> `Expression`<br>
`Consqeuence`		——> `Expression`<br>
`Alternate`		——> `Expression` | `Empty`<br>
`Program`		——> `CommandOrDefinition*`<br>
`CommandOrDefinition`   ——> `Command`<br>
	　　　　　| `Definition`<br>
	　　　　　| `(begin CommandOrDefinition+)`<br>

`Definition`		——> `(define Variable Expression)`<br>
	　　　　　| `(define (Variable DefFormals) Body)`<br>

`DefFormals` 		——> `Variable*`<br>
	　　　　　| `Variable* . Variable`<br>
