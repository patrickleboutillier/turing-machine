module Turing.Base (Symbol, Domain, blankSym, Operation(L, R, P, E), normalizeOperations, Tape(Tape), showTapeWith, blankTape, readSymbol, apply) where


-- A symbol is what can be printed on the tape of a Turing machine. 
-- We use a string because sometime a symbol can use more than one character.
type Symbol = String

-- A Domain is the list of all characters that can be read encountered a machine. 
-- It is not specificaly mentionned in the paper/book, but there are many cases 
-- where we need to know 
type Domain = [Symbol]

-- What we use to represent a tape square that was nothing on it. 
blankSym = " " 


-- Our tape. Squares to the left, the current square, squares to the right.
data Tape = Tape [Symbol] Symbol [Symbol]
-- Display the tape as a series of squares, with current square surrounded by 
-- square brackets.
instance Show Tape where 
  show tt = showTapeWith ("[", "]") tt

-- Allows to show a Tape with custom delimiters.
showTapeWith :: (String, String) -> Tape -> String
showTapeWith (b, a) (Tape ls h rs) = (p ls) ++ (b ++ h ++ a) ++ (p rs) ++ "|"
  where p [] = "|"  
        p cs = concat . map (\x -> "|" ++ x) $ cs 

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

readSymbol :: Tape -> Symbol 
readSymbol (Tape _ h _) = h


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
-- only one Symbol, and therefore the matched Symbol can be passed as a parameter.
normalizeOperations :: Symbol -> [Operation] -> [[Operation]]
normalizeOperations s [] = [[P s, N]]
normalizeOperations s xs = normOps s xs
  where normOps s [] = []   
        normOps s (E:ops) = normOps s (P blankSym:ops)
        normOps s (L:ops) = [P s, L] : normOps s ops
        normOps s (R:ops) = [P s, R] : normOps s ops
        normOps s (N:ops) = [P s, N] : normOps s ops
        normOps s (P c:L:ops) = [P c, L] : normOps s ops
        normOps s (P c:R:ops) = [P c, R] : normOps s ops
        normOps s (P c:ops) = [P c, N] : normOps s ops