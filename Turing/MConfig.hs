
module Turing.MConfig (SymbolSpec, matches, MConfig(..), Behaviour(..), MCH(..), (==>), asTable) where


import Turing.Base
import Data.Maybe
import Data.List


-- The Named class is to name things, it is used in MFunction
class Named a where
  named :: a -> String
instance (Named a, Named b) => Named (a, b) where
  named (a, b) = "(" ++ named a ++ "," ++ named b ++ ")"
instance (Named a, Named b, Named c) => Named (a, b, c) where
  named (a, b, c) = "(" ++ named a ++ "," ++ named b ++ "," ++ named c ++ ")"
instance (Named a, Named b, Named c, Named d) => Named (a, b, c, d) where
  named (a, b, c, d) = "(" ++ named a ++ "," ++ named b ++ "," ++ named c ++ "," 
    ++ named d ++" )"
instance (Named a, Named b, Named c, Named d, Named e) => Named (a, b, c, d, e) where
  named (a, b, c, d, e) = "(" ++ named a ++ "," ++ named b ++ "," ++ named c ++ "," 
    ++ named d ++ "," ++ named e ++ ")"
instance (Named a, Named b, Named c, Named d, Named e, Named f) => Named (a, b, c, d, e, f) where
  named (a, b, c, d, e, f) = "(" ++ named a ++ "," ++ named b ++ "," ++ named c ++ "," 
    ++ named d ++ "," ++ named e ++ "," ++ named f ++ ")"


-- A SymbolSpec is used to define rules to match a symbol.
data SymbolSpec = SSBlank | SSNone | SSAny | SSSym Symbol | SSNot Symbol | SSOneOf [Symbol] | SSNotOneOf [Symbol]
instance Show SymbolSpec where 
  show SSBlank = "(.*)"
  show SSNone = "( )"
  show SSAny = "(.+)"
  show (SSSym s) = "(" ++ s ++ ")"
  show (SSNot s) = "!(" ++ s ++ ")"
  show (SSOneOf cs) = "(" ++ (concat . intersperse "|" $ cs) ++ ")"
  show (SSNotOneOf cs) = "!(" ++ (concat . intersperse "|" $ cs) ++ ")"

matches :: SymbolSpec -> Symbol -> Bool
matches (SSBlank) s = True
matches (SSNone) s = s == blankSym
matches (SSAny) s = not $ s == blankSym
matches (SSSym c) s = s == c
matches (SSNot c) s = (not $ s == blankSym) && (not $ s == c)
matches (SSOneOf cs) s = or . map (== s) $ cs
matches (SSNotOneOf cs) s = (not $ s == blankSym) && (not . or . map (== s) $ cs)

-- Expand the given SymbolSpec to a list of Sym specs.
normalizeSpec :: Domain -> SymbolSpec -> [SymbolSpec]
normalizeSpec ss SSBlank = map SSSym ss
normalizeSpec ss SSAny = map SSSym . delete blankSym $ ss
normalizeSpec ss (SSSym s) = [SSSym s]
normalizeSpec ss (SSNot s) | s `elem` ss = map SSSym . delete blankSym . delete s $ ss
                         | otherwise =  map SSSym . delete blankSym $ ss
normalizeSpec ss (SSOneOf cs) = map SSSym cs


-- An MConfig is made up of 2 parts: the SymbolSpec and the Behaviour
data MConfig = MConfig String [(SymbolSpec, Behaviour)] 
instance Show MConfig where 
  show (MConfig name cbs) = init . concat $ map (\cb -> name ++ "\t-> " ++ showcb cb ++ "\n") cbs 
    where showcb (sspec, b) = (show sspec) ++ "\t-> " ++ (show b)
  showList (m:ms) = shows m . ("\n" ++) . showList ms
  showList [] = id
instance Named MConfig where 
  named (MConfig n _) = n

data Behaviour = Behaviour [Operation] MConfig
instance Show Behaviour where 
  show (Behaviour ops (MConfig name _)) = show ops ++ "\t-> " ++ name

data MCH = None [Operation] MConfig -- | SSAny | SSSym Symbol | SSNot Symbol | SSOneOf [Symbol] | SSNotOneOf [Symbol]

-- Helper function to create m-configurations
mConfig :: String -> [MCH] -> MConfig
mConfig name = MConfig name . map mCH2MConfig
  where mCH2MConfig (None ops fmc) = (SSNone, Behaviour ops fmc)
(==>) name mchs = mConfig name mchs

--mFunction :: (Named a) => String -> a -> [(SymbolSpec, [Operation], MConfig)] -> MConfig
--mFunction n params = mConfig (n ++ named params)
--mF :: (Named a) => String -> a -> [(SymbolSpec, [Operation], MConfig)] -> MConfig
--mF = mFunction 

traverseMConfigs :: (MConfig -> a) -> MConfig -> [a]
traverseMConfigs f = reverse . map snd . traverse [] f 
    where traverse :: [(String, a)] -> (MConfig -> a) -> MConfig -> [(String, a)]
          traverse seen f m@(MConfig name cbs) | isJust . lookup name $ seen = seen  
                                               | otherwise = foldl (\acc (sspec, Behaviour ops fmc) -> traverse acc f fmc) ((name, f m):seen) cbs

asTable = traverseMConfigs id

-- Makes sure that all SymbolSpecs are Ps
normalizeMConfigSpecs :: Domain -> MConfig -> MConfig
normalizeMConfigSpecs dom = step
    where step (MConfig name cbs) = MConfig name . concat . map (\(sspec, Behaviour ops fmc) -> map (\s -> (s, Behaviour ops $ step fmc)) . normalizeSpec dom $ sspec) $ cbs

-- Makes sure all operations follow the normal forms from page 134. normalizeMConfigSpecs must have 
-- been applied before!
normalizeMConfigOps :: MConfig -> MConfig
normalizeMConfigOps = step
    where step (MConfig name cbs) = MConfig name . map (\(sspec@(SSSym s), Behaviour ops fmc) -> (sspec, splitBehaviour name sspec . Behaviour ops $ step fmc)) $ cbs

splitBehaviour :: String -> SymbolSpec -> Behaviour -> Behaviour
splitBehaviour name sspec@(SSSym s) (Behaviour ops fmc) = (\(MConfig name cbs) -> snd . head $ cbs) . foldr (\ops m -> MConfig (nname ops) [(sspec, (Behaviour ops m))]) fmc $ ns
    where ns = normalizeOperations s ops 
          nname ops = name ++ show sspec ++ show ops

-- Replaces all name with the standard notation. normalizeMConfigSpecs and normalizeMConfigOps must 
-- have been applied before!
normalizeNames :: MConfig -> MConfig
normalizeNames m = step m
    where step (MConfig name cbs) = MConfig (nname name) . map (\(sspec, Behaviour ops fmc) -> (sspec, Behaviour ops $ step fmc)) $ cbs
          names = traverseMConfigs (\(MConfig name _) -> name) m
          nmap = zip names $ map (\n -> "q" ++ show n) [1..]
          nname n = fromJust . lookup n $ nmap 

-- Replaces all name with the standard notation. normalizeMConfigSpecs and normalizeMConfigOps must have been applied before!
normalizeSymbols :: Domain -> MConfig -> MConfig
normalizeSymbols dom m = step m
    where step (MConfig name cbs) = MConfig name . map (\(SSSym s, Behaviour (P c:o:[]) fmc) -> (SSSym (ns s), Behaviour [P . ns $ c, o] $ step fmc)) $ cbs
          smap = zip dom $ map (\n -> "S" ++ show n) [0..]
          ns s = fromJust . lookup s $ smap

normalizeMConfig :: Domain -> MConfig -> MConfig
normalizeMConfig dom m = normalizeSymbols dom . normalizeNames . normalizeMConfigOps . normalizeMConfigSpecs dom $ m

standardForm :: Domain -> MConfig -> String
standardForm dom = concat . map sf . asTable . normalizeMConfig dom
    where sf (MConfig name [(SSSym s, Behaviour (P c:o:[]) (MConfig name' _))]) = name ++ s ++ c ++ show o ++
                                                                                  name' ++ ";" 

standardDesc :: Domain -> MConfig -> String
standardDesc dom = form2desc . standardForm dom
    where form2desc [] = []
          form2desc (s:ss) | s == 'q' = 'D' : (num2A . takeWhile num $ ss) ++ (form2desc (dropWhile num ss))
                           | s == 'S' = 'D' : (num2C . takeWhile num $ ss) ++ (form2desc (dropWhile num ss))
                           | otherwise = s : form2desc ss
          num = (\s -> s >= '0' && s <= '9')
          num2A ns = replicate (read ns) 'A'
          num2C ns = replicate (read ns) 'C'

standardTape :: Domain -> MConfig -> Tape
standardTape dom mconfig = Tape [] "e" $ "e":";":blankSym:ss
    where squares = concat . map (\c -> [[c], blankSym]) . standardDesc dom $ mconfig
          ss = (init . init $ squares) ++ ["::"]

descNumber :: Domain -> MConfig -> String
descNumber dom = map desc2num . standardDesc dom
    where desc2num 'A' = '1'
          desc2num 'C' = '2'
          desc2num 'D' = '3'
          desc2num 'L' = '4'
          desc2num 'R' = '5'
          desc2num 'N' = '6'
          desc2num ';' = '7'




{--
-- page 81
mcs81 = [
        mConfig "b" [([blank], [P '0', R], "c")],
        mConfig "c" [([blank], [R], "e")],
        mConfig "e" [([blank], [P '1', R], "f")],
        mConfig "f" [([blank], [R], "b")]
    ]
m81 = newTM mcs81 "b"
b81 s | mNone s = mBehaviour "b81" [P '0', R] c81  
c81 s | mNone s = mBehaviour "c81" [R]  e81
e81 s | mNone s = mBehaviour "e81" [P '1', R] f81
f81 s | mNone s = mBehaviour "f81" [R] b81
mf81 = newFTM b81 ""
-- page 87
b87 s | mNone s         = mBehaviour "b87" [P 'e', R, P 'e', R, P '0', R, R, P '0', L, L] o87
o87 '1'                 = mBehaviour "o87" [R, P 'x', L, L, L] o87
o87 '0'                 = mBehaviour "o87" [] q87
q87 s | not . mNone $ s = mBehaviour "q87" [R, R] q87
q87 s | mNone s         = mBehaviour "q87" [P '1', L] p87
p87 'x'                 = mBehaviour "p87" [E, R] q87
p87 'e'                 = mBehaviour "p87" [R] f87
p87 s | mNone s         = mBehaviour "p87" [L, L] p87
f87 s | not . mNone $ s = mBehaviour "f87" [R, R] f87
f87 s | mNone s         = mBehaviour "f87" [P '0', L, L] o87
m87 = newFTM b87 "ex"
--}