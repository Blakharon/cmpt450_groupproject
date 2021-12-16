## README

### Running the Simulations

Running the simulations is fairly similar to assignment3 for the cache based task. For ours you can choose to run it on 3 different image sizes: 5x5 pixels, 15x15 pixels, and 25x25 pixels.

We will look at the 25x25 example. To run the 25x25 example for Push-Relabel algorithm you will need to call the shell script "model_25.sh" with the following command:

    "./model_25.sh -t model_25 -b flow -p"

To run the Edmonds-Karp algorithm, you will need to call the same shell script but with this command instead:

    "./model_25.sh -t model_25 -b flow_e_k -p"

### Plots

Since we have all the data already saved in the folder "outputs/", creating the graphs is fairly easy. You will need the following Python3 libraries: numpy, pandas, seaborn, matplotlib

Once you have those libraries you can call the following command on the plots.py script:

    "python3 plots.py"