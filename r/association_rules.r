# Завантаження бібліотек
if(!require(arules)) install.packages("arules")
library(arules)
if(!require(arulesViz)) install.packages("arulesViz")
library(arulesViz)
if(!require(RColorBrewer)) install.packages("RColorBrewer")
library(RColorBrewer)

custom_groceries <- list()
custom_groceries[[1]] <- c("яблука","помідори","цукерки","картопля","цибуля")
custom_groceries[[2]] <- c("яблука","морква","помідори","цукерки","картопля")
custom_groceries[[3]] <- c("яблука","морква","помідори","цукерки","цибуля")
custom_groceries[[4]] <- c("банани","цукерки","картопля","цибуля")
custom_groceries[[5]] <- c("помідори","цукерки","картопля")
custom_groceries[[6]] <- c("персик","слива","цибуля")
custom_groceries[[7]] <- c("яблука","цукерки","картопля")
custom_groceries[[8]] <- c("яблука","помідори","персик","картопля","цибуля")
custom_groceries[[9]] <- c("яблука","банани","цукерки","цибуля")
custom_groceries[[10]] <- c("яблука","банани","помідори","салат","цукерки","картопля")
custom_groceries[[11]] <- c("яблука","помідори","картопля")
custom_groceries[[12]] <- c("яблука","помідори","салат","картопля","слива","цибуля")
custom_groceries[[13]] <- c("яблука","цукерки","картопля","слива","цибуля")
custom_groceries[[14]] <- c("яблука","морква","помідори","персик","картопля","слива","цибуля")
custom_groceries[[15]] <- c("яблука","морква","помідори","цукерки","картопля","слива","цибуля")
custom_groceries[[16]] <- c("яблука","банани","цукерки","картопля","слива","цибуля")
custom_groceries[[17]] <- c("банани","цукерки","картопля")
custom_groceries[[18]] <- c("помідори","цукерки","персик","картопля","слива","цибуля")
custom_groceries[[19]] <- c("яблука","морква","цукерки","картопля","цибуля")
custom_groceries[[20]] <- c("яблука","помідори","цукерки","картопля","цибуля")
Groceries <- transactions(custom_groceries)
inspect(Groceries)

frequent <- eclat(Groceries, parameter=list(supp = 0.10, maxlen=2))
frequent <- sort(frequent, by = 'support')
inspect(frequent)

arules::itemFrequencyPlot(Groceries, topN = 20, 
                          col = brewer.pal(8, 'Pastel2'),
                          main = 'Relative Item Frequency Plot',
                          type = "relative",
                          ylab = "Item Frequency (Relative)")

rules <- apriori(Groceries, parameter = list(supp = 0.12,conf = 0.8, maxlen = 5))
inspect(rules)