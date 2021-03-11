module Turing.Base (Symbol, Domain, blankSym, Operation(L, R, P, E), SymbolSpec(..), matches, normalizeOps, normalizeSpec, Tape(Tape), showTapeWith, blankTape, scanSymbol, apply) where

import Data.List 

-- A symbol is what can be printed on/scanned from the tape of a Turing machine.
-- We use a string because sometimes a symbol can use more than one character (i.e. '::'
-- Also, having a string will be handy when we work on normalizing the Symbols, as this 
-- is done using generic names like S0, S1, S2, ...
type Symbol = String

-- A Domain is the list of all characters that can be encountered by a machine. 
-- It is not specificaly mentionned in the paper/book, but there are many cases 
-- where we need to have this information handy (i.e. when we encounter symbol 
-- specifications like Blank, Any, ...  
type Domain = [Symbol]

-- What we use to represent a tape square that was nothing on it, simply a space character. 
blankSym = " " 


-- A SymbolSpec is used to define rules to match a symbol.
data SymbolSpec = Blank | None | Any | Sym Symbol | Not Symbol | OneOf [Symbol] | NotOneOf [Symbol]
instance Show SymbolSpec where 
  show Blank = "(.*)"
  show None = "' '"
  show Any = "(.+)"
  show (Sym s) = "'" ++ s ++ "'"
  show (Not s) = "!'" ++ s ++ "'"
  show (OneOf cs) = "('" ++ (concat . intersperse "'|'" $ cs) ++ "')"
  show (NotOneOf cs) = "!('" ++ (concat . intersperse "'|'" $ cs) ++ "')"

-- Returns true is the SymbolSpec matches the given Symbol. 
matches :: SymbolSpec -> Symbol -> Bool
matches (Blank) s = True
matches (None) s = s == blankSym
matches (Any) s = not $ s == blankSym
matches (Sym c) s = s == c
matches (Not c) s = (not $ s == blankSym) && (not $ s == c)
matches (OneOf cs) s = or . map (== s) $ cs
matches (NotOneOf cs) s = (not $ s == blankSym) && (not . or . map (== s) $ cs)

-- Normalizes a SymbolSpec to list of SymbolSpec matching only one specific character (i.e. Sym s).
-- To do this may require the machines Domain, for example to expand Any into the list of all possible
-- symbols used in the machine. 
normalizeSpec :: Domain -> SymbolSpec -> [SymbolSpec]
normalizeSpec ss Blank = map Sym ss
normalizeSpec ss None = [Sym blankSym]
normalizeSpec ss Any = map Sym . delete blankSym $ ss
normalizeSpec ss (Sym s) = [Sym s]
normalizeSpec ss (Not s) = map Sym . delete blankSym . delete s $ ss
normalizeSpec ss (OneOf cs) = map Sym cs
normalizeSpec ss (NotOneOf cs) = map Sym . delete blankSym $ ss \\ cs


-- Our tape. Squares to the left, the current square, squares to the right.
data Tape = Tape [Symbol] Symbol [Symbol]
-- Display the tape as a series of squares, with current square surrounded by 
-- square brackets.
instance Show Tape where 
  show tt = showTapeWith ("[", "]") tt

-- Allows to show a Tape with custom delimiters.
showTapeWith :: (String, String) -> Tape -> String
showTapeWith (b, a) (Tape ls h rs) = "[" ++ (concat . intersperse "|" $ ls ++ [b++h++a] ++ rs) ++ "]"
 -- (p ls) ++ (b ++ h ++ a) ++ (p rs) ++ "|"
  --where p [] = "|"  
  --      p cs = concat . map (\x -> "|" ++ x) $ cs 

-- A blank tape
blankTape = Tape [] blankSym []

moveLeft :: Tape -> Tape
moveLeft (Tape [] h rs) = Tape [] blankSym $ h:rs
moveLeft (Tape ls h rs) = Tape (init ls) (last ls) $ h:rs

moveRight :: Tape -> Tape
moveRight (Tape ls h []) = Tape (ls++[h]) blankSym []
moveRight (Tape ls h (r:rs)) = Tape (ls++[h]) r rs

printSymbol :: Symbol -> Tape -> Tape
printSymbol sym (Tape ls h rs) = Tape ls sym rs

eraseSymbol :: Tape -> Tape
eraseSymbol = printSymbol blankSym

scanSymbol :: Tape -> Symbol 
scanSymbol (Tape _ h _) = h


-- The different tape operations that can be used in m-configurations 
data Operation = L | R | E | N | P Symbol 
  deriving (Show)

-- Apply the operation to the tape.
apply :: Operation -> Tape -> Tape
apply L = moveLeft
apply R = moveRight
apply E = eraseSymbol
apply (P c) = printSymbol c
apply N = id

-- Breaks up a list of operations into one of the normal forms described in TAT page 134.
-- This implies that the m-config line in question has already been normalized to matching 
-- only one Symbol (see normalizeSpec), and therefore the matched Symbol can be passed as a parameter.
normalizeOps :: Symbol -> [Operation] -> [[Operation]]
normalizeOps s [] = [[P s, N]]
normalizeOps s xs = normOps s xs
  where normOps s [] = []   
        normOps s (E:ops) = normOps s (P blankSym:ops)
        normOps s (L:ops) = [P s, L] : normOps s ops
        normOps s (R:ops) = [P s, R] : normOps s ops
        normOps s (N:ops) = [P s, N] : normOps s ops
        normOps s (P c:L:ops) = [P c, L] : normOps s ops
        normOps s (P c:R:ops) = [P c, R] : normOps s ops
        normOps s (P c:ops) = [P c, N] : normOps s ops