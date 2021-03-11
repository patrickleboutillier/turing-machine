module Turing.MConfig ((==>), asList, MCH(..), MConfig(..), Behaviour(..), 
  Turing.Base.Symbol, Turing.Base.blankSym, Turing.Base.matches, Turing.Base.Domain, Turing.Base.Operation(..)) where


import Turing.Base
import Data.Maybe
import Data.List


-- An MConfig is made up of 2 parts: the SymbolSpec and the Behaviour
data MConfig = MConfig String [(SymbolSpec, Behaviour)]
instance Show MConfig where 
    show (MConfig name cbs) = init . concat $ map (\cb -> name ++ "\t-> " ++ showcb cb ++ "\n") cbs 
        where showcb (sspec, b) = (show sspec) ++ "\t-> " ++ (show b)
    showList (m:ms) = shows m . ("\n" ++) . showList ms
    showList [] = id

data Behaviour = Behaviour [Operation] MConfig
instance Show Behaviour where 
    show (Behaviour ops (MConfig name _)) = show ops ++ "\t-> " ++ name

data MCH = Blank [Operation] MConfig | None [Operation] MConfig | Any [Operation] MConfig |
                 Sym Symbol [Operation] MConfig | Not Symbol [Operation] MConfig | 
                 OneOf [Symbol] [Operation] MConfig | NotOneOf [Symbol] [Operation] MConfig

(==>) :: String -> [MCH] -> MConfig
(==>) name mchs = MConfig name $ map cnv mchs
   where cnv (Turing.MConfig.Blank ops fmc) = (Turing.Base.Blank, Behaviour ops fmc)
         cnv (Turing.MConfig.None ops fmc) = (Turing.Base.None, Behaviour ops fmc)
         cnv (Turing.MConfig.Any ops fmc) = (Turing.Base.Any, Behaviour ops fmc)
         cnv (Turing.MConfig.Sym s ops fmc) = (Turing.Base.Sym s, Behaviour ops fmc)
         cnv (Turing.MConfig.Not s ops fmc) = (Turing.Base.Not s, Behaviour ops fmc)
         cnv (Turing.MConfig.OneOf ss ops fmc) = (Turing.Base.OneOf ss, Behaviour ops fmc)
         cnv (Turing.MConfig.NotOneOf ss ops fmc) = (Turing.Base.NotOneOf ss, Behaviour ops fmc)

asList :: MConfig -> [MConfig]
asList = reverse . map snd . traverse [] 
    where traverse :: [(String, MConfig)] -> MConfig -> [(String, MConfig)]
          traverse seen m@(MConfig name cbs) | isJust . lookup name $ seen = seen  
                                             | otherwise = foldl (\acc (sspec, Behaviour ops fmc) -> traverse acc fmc) ((name, m):seen) cbs