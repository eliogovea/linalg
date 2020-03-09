# Matrix C++

- a generic ```matrix``` class with template parameters to define the data type of the values (```T```) and the matrix dimensions (```N```, ```M```) that keeps values data in a std::array<T, N * M>. Usage example:

   ```cpp
    auto A = matrix<double, 2, 3> = {
       1, 1,
       1, 0
    };
    ```

- ```vector``` can be represented as an special matrix with only one so only an alias would be enough

    ```cpp
    template <typename T, std::size_t N>
    using vector = matrix<T, N, 1>;
    ```

- ```matrix_view``` class was created aiming to have a lightweigh way to access and modity data from the matrix and also define rows or columns or even diagonals. ```matrix_view``` is a generic class that takes as template parametes ```T```, ```S``` ans ```D``` representing the data type, the size of the view (e.g. for a row it would be the number of columns) and the space between two elements of the view in the original data.

- all the classes are defined in the files inside ```/include/linalg```

- the project is structured as a headers only library and you can build the demo using cmake

    ```bash
    mkdir build
    cd build
    cmake .. -DDEMO=ON
    make .
    ```
