if(!require(neuralnet)) install.packages("neuralnet")
library(neuralnet)

# Вхідні та вихідні дані
input_data <- c(1,3,6,8,9,10,11,12,14,16,17,18,20,22,23,24,25,27,29,30)
output_data <- c(-26,-18,-6,2,6,10,14,18,26,34,38,42,50,58,62,66,70,78,86,90)
data <- data.frame(input_data, output_data)
normalize <- function(x) {
  return ((x - min(x)) / (max(x) - min(x)))
}
data <- as.data.frame(lapply(data , normalize))

# Розділення даних на навчальну та тестову вибірки
train_partition <- 0.75
set.seed(123)  # Встановлення seed для відтворюваності результатів
train_index <- sample(1:nrow(data), train_partition * nrow(data))
train_data <- data[train_index, ]
test_data <- data[-train_index, ]

# Створення та навчання нейронної мережі
neural_net <- neuralnet(
  output_data ~ input_data,
  data = train_data,
  hidden = c(2),
  act.fct="tanh")
plot(neural_net, rep = "best")

# Тестування навченої мережі на тестовій вибірці
predicted <- predict(neural_net, test_data)
print(test_data$output_data)
print(predicted[,1])

error = abs(as.numeric(test_data$output_data) - as.numeric(predicted[,1]))
accuracy = (1 - (sum(error)/nrow(test_data))) * 100
print(accuracy)