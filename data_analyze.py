import numpy as np
#%%read file
dataset = []

# Open the original file and a new file to save the results
file_path = 'choice_output2.txt'
output_file_path = 'choice_filtre2.txt'

with open(file_path, 'r') as input_file, open(output_file_path, 'w') as output_file:
    # Iterate through each line in the original file
    for line in input_file:
        # Calculate the length of the line
        line_length = len(line.strip())

        # If the line length is between 10 and 18 (inclusive), write it to the new file
        if 10 <= line_length <= 18:
            output_file.write(line)
        
#%% read the data
with open(output_file_path, 'r') as file:
    # skip the heading
    file.readline()

    while True:
        # obtain the second line
        line = file.readline()
        if not line:
            break

        # split the string with respect to comma
        str_list = line.split(',')
        #change data type to string
        float_list = [float(x) for x in str_list if x.strip()]  # filter void string
        dataset.append(float_list)
        
#filtre dataset
filtered_set = [sublist for sublist in dataset if len(sublist) == 4]
#change to array
data_array = np.array(filtered_set)

#extract experiment data from each row
t_exp = data_array[:, 0]
sensorReading = data_array[:, 1]
t_react = data_array[:, 3]
#filter 0 and unnormal data
react_f = t_react[(t_react != 0) & (t_react >= 100) & (t_react <= 600)] #set filter standard with respect to occasion
react_r = t_react[(t_react != 0)]
sensor_f = sensorReading[(sensorReading != 0)]

#normalize the distribution
def z_score_normalize(data):
    mean_val = np.mean(data)
    std_dev = np.std(data)
    normalized_data = (data - mean_val) / std_dev
    return normalized_data

react_n = z_score_normalize(react_f)


#%%plot
import matplotlib.pyplot as plt
from scipy.stats import norm
from scipy import stats
# plot a frequency density histogram for time
plt.hist(react_f, bins=25, density=True) 
# set the label and titles
plt.title('Probability Diagram')
plt.xlabel('Reaction time/ms')
plt.ylabel('Frequency Density')
#result shall looks like a normal distribution
plt.show()

# Generate x values for the PDF curve
x_values = np.linspace(min(react_n), max(react_n), 100)
# Calculate the probability density function of the normal distribution
pdf_values = norm.pdf(x_values)

# Plot the distribution curve
plt.plot(x_values, pdf_values, 'r-', label='Normalised Possibility Distribution')
plt.show()

# plot a frequency density diagram for force
plt.hist(sensor_f, bins=range(int(min(sensor_f)), int(max(sensor_f)) + 10, 50), density=True)
# set the label and titles
plt.title('Probability Diagram')
plt.xlabel('Force')
plt.ylabel('Frequency Density')
#result shall looks like a normal distribution
plt.show()

#%%stat for reaction time
print("minimum =", np.min(react_f))
print("maximum =", np.max(react_f))
print('sample size = ', react_r.size)
print('mean reaction time =',np.mean(react_f))
print('variance =',np.var(react_f))
print('standard deviation =',np.std(react_f))
print('median =', np.median(react_f))
print('mode =', stats.mode(react_f)[0][0])
#stat for sensor
print('minimum =',np.min(sensor_f))
print('maximum =',np.max(sensor_f))
print('mean force applied =',np.mean(sensor_f))
print('variance =',np.var(sensor_f))
print('standard deviation =',np.std(sensor_f))
print('median =', np.median(sensor_f))