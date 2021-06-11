#include "../src/CuckooHashing.cpp"

int main(int argc, char** argv) {
    if(argc != 1 && argc != 3){
        std::cout << "0 or 2 parameter(s) accepted." << std::endl;
        return 0;
    }

    int testCount = TEST_COUNT, unitsLen = UNITS_LEN * SLOTS_NUM;
    if(argc == 3)
        testCount = atoi(argv[1]), unitsLen = atoi(argv[2]);

    // generate no-repeat sequence to insert
    std::unordered_set<int> s;
    for(int i=0; i<testCount; i++){
        int value = e();
        while(s.count(value))
            value = e();
        s.insert(value);
    }
    std::vector<int> seq(s.begin(), s.end());

    // init a CuckooHashing
    CuckooHashing* cuckoo = new CuckooHashing(unitsLen);

    // test Insert
    clock_t start, end;
    start = clock();
    for(int i=0; i<testCount; i++){
        if(!cuckoo->Insert(seq[i])){
            std::cout << "Insert " << seq[i] << " error!" << std::endl;
            return -1;
        }
    }
    end = clock();
    std::cout << "Insert TimeCost = " << double(end - start) * 1000 / CLOCKS_PER_SEC << " ms" << std::endl;

    // test Search
    start = clock();
    for(int i=0; i<testCount; i++){
        if(!cuckoo->Search(seq[i])){
            std::cout << "Search " << seq[i] << " error!" << std::endl;
            return -1;
        }
    }
    end = clock();
    std::cout << "Search TimeCost = " << double(end - start) * 1000 / CLOCKS_PER_SEC << " ms" << std::endl;

    // test Delete
    start = clock();
    for(int i=0; i<testCount; i++){
        if(!cuckoo->Delete(seq[i])){
            std::cout << "Delete " << seq[i] << " error!" << std::endl;
            return -1;
        }
    }
    end = clock();
    std::cout << "Delete TimeCost = " << double(end - start) * 1000 / CLOCKS_PER_SEC << " ms" << std::endl;

    // test Search
    start = clock();
    for(int i=0; i<testCount; i++){
        if(cuckoo->Search(seq[i])) {
            std::cout << "Search " << seq[i] << " error!" << std::endl;
            return -1;
        }
    }
    end = clock();
    std::cout << "Search TimeCost = " << double(end - start) * 1000 / CLOCKS_PER_SEC << " ms" << std::endl;

    std::cout << "Crash Time = " << cuckoo->crash << std::endl;

    std::cout << "PASS!" << std::endl;
    return 0;
}
