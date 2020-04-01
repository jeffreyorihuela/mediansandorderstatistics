#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int partition(vector<int> &input_, int start, int end, int pivot)
{
    int aux = input_[pivot];
    input_[pivot] = input_[end];
    input_[end] = aux;

    int i = start - 1;
    for (int j = start; j <= end - 1; j++)
    {
        if (input_[j] < input_[end])
        {
            i++;
            int aux = input_[j];
            input_[j] = input_[i];
            input_[i] = aux;
        }
    }

    aux = input_[end];
    input_[end] = input_[i + 1];
    input_[i + 1] = aux;
    
    return i + 1; //retorno el indice del item que esta en la posicion correcta
}

int quickselect(vector<int> &input_, int start, int end, int k)  //Expected time O(n)
{
    int pivot = start + (rand() % (end-start + 1));
    int index = partition(input_, start, end, pivot);
    if (index == k)
    {
        return input_[index];
    }
    else if (k < index)
    {
        return quickselect(input_, start, index-1, k);
    }
    else
    {
        return quickselect(input_, index+1, end, k);   
    }
    
}

/**    Select deterministic worst time N      **/

int median(vector<int> &input_)
{
    sort(input_.begin(), input_.end());
    return input_[input_.size()/2];
};

int partitionModified(vector<int> &input_, int medianOfmedians)
{
    int index;
    for (int i = 0; i < input_.size(); i++)
    {
        if(input_[i] == medianOfmedians) index=i;
    }
    input_[index] = input_[input_.size()-1];
    input_[input_.size()-1] = medianOfmedians;
    int j = -1;
    for (int i = 0; i < input_.size()-1; i++)
    {
        if(input_[i] < medianOfmedians)
        {
            j++;
            int aux = input_[i];
            input_[i] = input_[j];
            input_[j] = aux;
        }
    }
    input_[input_.size()-1] = input_[j+1];
    input_[j+1] = medianOfmedians;
    return j+1;
}

int kthSmallest(vector<int> input_, int k) 
{
    vector<int> medians;
    int i;
    for (i = 0; i < input_.size()/5; i++)
    {
        vector<int> input_split;
        input_split.assign(input_.begin()+(i*5), input_.begin()+(i*5)+5);
        int median_ = median(input_split);
        medians.push_back(median_);
    }
    if (i*5<input_.size())
    {
        vector<int> input_split;
        input_split.assign(input_.begin()+(i*5), input_.begin()+(i*5)+input_.size()%5);
        int median_ = median(input_split);
        medians.push_back(median_);
        i++;
    }
    int medianOfmedians = (i == 1)? medians[i-1]
                                :kthSmallest(medians, medians.size()/2);

    int index = partitionModified(input_, medianOfmedians);
    
    if(index == k)
    {
        return input_[k];
    }
    if(k < index)
    {
        vector<int> lowSide;
        lowSide.assign(input_.begin(),input_.begin()+index);
        return kthSmallest(lowSide, k);
    }
    vector <int> highSide;
    highSide.assign(input_.begin()+index+1,input_.end());
    return kthSmallest(highSide, k-index-1);

};

int main()
{
    vector<int> input_;
    for (int i = 1; i <= 124; i++)
        input_.push_back(i);

    random_shuffle(input_.begin(), input_.end());

    // for (vector<int>::iterator it = input_.begin(); it != input_.end(); it++)
    //     cout << *it << " ";
    // cout << "\n";
    
    
    // int k;
    // while(k != -1)
    // {
    //     cin >> k;
    //     cout << quickselect(input_, 0, input_.size()-1, k)<< '\n';
    // }

    cout << kthSmallest(input_,  input_.size()/2);
}