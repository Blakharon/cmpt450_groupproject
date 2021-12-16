## README

### Running the Simulations

Running the simulations is fairly similar to assignment3 for the cache based task. For ours you can choose to run it on 3 different image sizes: 5x5 pixels, 15x15 pixels, and 25x25 pixels.

We will look at the 25x25 example. To run the 25x25 example for Push-Relabel algorithm you will need to call the shell script "model_25.sh" with the following command:

    "./model_25.sh -t model_25 -b flow -p"

To run the Edmonds-Karp algorithm, you will need to call the same shell script but with this command instead:

    "./model_25.sh -t model_25 -b flow_e_k -p"

In order to run it on the 15x15 image sizes, you can change "model_25" to "model_15", and for the 5x5 examples you can change "model_25" to "model".

To change the example image you can edit the model_25.sh scripts. There is a line called:

    INPUT="inputs/mnist/bin/circle_25x25_5.bin"

There are 6 images. You can change circle_25x25_5 to circle_25x25_0, circle_25x25_1, circle_25x25_2, circle_25x25_3, or circle_25x25_4.

### Plots

Since we have all the data already saved in the folder "outputs/", creating the graphs is fairly easy. You will need the following Python3 libraries: numpy, pandas, seaborn, matplotlib

Once you have those libraries you can call the following command on the plots.py script:

    "python3 plots.py"