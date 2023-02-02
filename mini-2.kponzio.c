int isEven(int numValues, int *values, int *results){
    
    for (int i =0; i<numValues; i++){
        if (values[i]%2 == 0){
            results[i] = 1;
        }
        else {
            results[i] = 0;
        }
    }
    return 0;
}