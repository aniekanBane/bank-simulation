# Bank Transaction Simulation

Simulation of common banking transactions.
This project is based of the C#101 tutorials on .NET series and Learning C# by Joe Marini on LinkedIn learning

## Getting Started

clone the repository and in your terminal do the following command

```bash
git clone https://github.com/aniekanBane/bank-simulation.git
```

## RUN

### C++

Create build directory

```shell
mkdir build && cd build
```

Build Cmake with BUILD_TESTS `OFF` (download boost to use enable testing)

```shell
cmake ../cpp -DBUILD_TESTS=OFF && cmake --build
```

Finally run the program

```shell
./Bank-CPP
```

### CSharp

```bash
dotnet run --project csharp/Bank
```

Or use vscode, you can clone it from there and run the program **easier**

### Operations

>**Images are from the csharp version**

- The start page

![startpage](/static/images/start.png)

- Account selection

![accounts](/static/images/accounts.png)

- Operations page

![selection](/static/images/selection.png)

- Example choice (List of Transactions)

![transcastions](/static/images/transactions.png)
