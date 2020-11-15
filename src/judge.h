#include <iostream>

#include <tuple>
#include <filesystem>
#include "gameSet.h"

#include "compiler.h"
#include "binaryrw.h"

// To chench
#include <fstream>

typedef filesystem::path path;
using namespace std;

class judge {
    private:

    public:

        template <typename T, typename U>
        size_t jdge(path path2file,
                    path outdir,
                    const GameSet<tuple<T, U>> &gs) {

            compiler cmpr {path2file, "/tmp/"};
            binaryrw bnrw {outdir};

            cmpr.run();
            bnrw.run();

            fstream file;
            file.open("inputs_user", ios::in | ios::out);
            string buf;

            // The actual veredict
            // Compares the inputs and the results
            // with the expected ones
            if (file.is_open())      //TODO: fix
                for (auto i: gs) {
                    file >> buf;
                    if (buf.compare(get<1>(i))) return 0;
                    buf = "";
                }
            file.close();
        return 1;
        }
};
