module Turing.StdForm () where


import Turing.Base
import Turing.MConfig
import Data.Maybe
import Data.List


-- From our recursive MConfig, we will create a Table that will make the tnansformation to standard form easier.
data Row = Row String SymbolSpec [Operation] String
instance Show Row where 
  show (Row mc ss ops fmc) = mc ++ "\t-> " ++ show ss ++ "\t-> " ++ show ops ++ "\t-> " ++ fmc
  showList (r:rs) = shows r . ("\n" ++) . showList rs
  showList [] = id

asRows :: MConfig -> [Row]
asRows = concat . map domc . asList 
    where domc (MConfig name cbs) = map (\(ss, Behaviour ops (MConfig fname _)) -> Row name ss ops fname) cbs

asTable :: Domain -> MConfig -> Table
asTable dom = Table dom . asRows  
 

data Table = Table Domain [Row]
instance Show Table where 
  show (Table dom rows) = init $ "m-configs over " ++ show dom ++ "\n" ++ show rows 


-- Makes sure that all SymbolSpecs are Ps
normalizeTableSpecs :: Table -> Table
normalizeTableSpecs (Table dom rows) = Table dom . concat . map normalizeRow $ rows 
  where normalizeRow (Row mc ss ops fmc) = map (\n -> Row mc n ops fmc) . normalizeSpec dom $ ss

-- Makes sure all operations follow the normal forms from page 134. normalizeMConfigSpecs must have 
-- been applied before!
normalizeTableOps :: Table -> Table
normalizeTableOps (Table dom rows) = Table dom . concat . map normalizeRow $ rows
  where normalizeRow (Row mc (Turing.Base.Sym s) ops fmc) = map (\n -> Row mc (Turing.Base.Sym s) n fmc) . normalizeOps s $ ops

getTableNames :: Table -> [String]
getTableNames (Table dom rows) = nub . reverse . foldl (\acc (Row mc ss ops fmc) -> fmc:mc:acc) [] $ rows 

normalizeTableNames :: Table -> Table
normalizeTableNames tbl@(Table dom rows) = Table dom . map (\(Row mc ss ops fmc) -> Row (lu mc) ss ops (lu fmc)) $ rows
  where lu n = fromJust . lookup n $ lut
        lut = zip (getTableNames tbl) nnames   
        nnames = map (\n -> "q" ++ show n) [1..]

normalizeTableSymbols :: Table -> Table
normalizeTableSymbols tbl@(Table dom rows) = Table dom . map (\(Row mc (Turing.Base.Sym s) [P c,o] fmc) -> Row mc (Turing.Base.Sym $ lu s) [P (lu c), o] fmc) $ rows
  where lu s = fromJust . lookup s $ lut
        lut = zip (sort dom) nnames 
        nnames = map (\n -> "S" ++ show n) [0..]

normalizeTable :: Table -> Table
normalizeTable = normalizeTableSymbols . normalizeTableNames . normalizeTableOps . normalizeTableSpecs 

toStandardForm :: Table -> String
toStandardForm = concat . (\(Table _ rows) -> map sf rows) . normalizeTable 
    where sf (Row mc (Turing.Base.Sym s) [P c,o] fmc) = mc ++ s ++ c ++ show o ++ fmc ++ ";" 

--fromStandardForm :: String -> Maybe Table
fromStandardForm s = groupBy (\a b -> b /= ';') s

toStandardDesc :: Table -> String
toStandardDesc = form2desc . toStandardForm 
    where form2desc [] = []
          form2desc (s:ss) | s == 'q' = 'D' : (num2A . takeWhile num $ ss) ++ (form2desc (dropWhile num ss))
                           | s == 'S' = 'D' : (num2C . takeWhile num $ ss) ++ (form2desc (dropWhile num ss))
                           | otherwise = s : form2desc ss
          num = (\s -> s >= '0' && s <= '9')
          num2A ns = replicate (read ns) 'A'
          num2C ns = replicate (read ns) 'C'

toStandardTape :: Table -> Tape
toStandardTape tbl = Tape [] "e" $ "e":";":blankSym:ss
    where squares = concat . map (\c -> [[c], blankSym]) . toStandardDesc $ tbl
          ss = (init . init $ squares) ++ ["::"]

toDescNumber :: Table -> String
toDescNumber = map desc2num . toStandardDesc
    where desc2num 'A' = '1'
          desc2num 'C' = '2'
          desc2num 'D' = '3'
          desc2num 'L' = '4'
          desc2num 'R' = '5'
          desc2num 'N' = '6'
          desc2num ';' = '7'


--}

dom = [" ", "0" ,"1"]
b = "b" ==> [Turing.MConfig.None    [P "0", R]      c]
c = "c" ==> [Turing.MConfig.None    [R]             e]
e = "e" ==> [Turing.MConfig.None    [P "1", R]      f]
f = "f" ==> [Turing.MConfig.None    [R]             b]

sf = toStandardForm . asTable dom $ b