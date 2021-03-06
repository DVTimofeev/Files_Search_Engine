#include "InvertedIndex.h"
#include "ConvertJSON.h"
#include "SearchEngine.h"

#include <iostream>
#include <chrono>
#include <algorithm>
#include <fstream>


int main(){
    ConvertJSON convertJSON;
    convertJSON.open_config("");
    convertJSON.open_requests("");
    if (convertJSON.get_error_msg().empty()){
        auto file_paths = convertJSON.get_file_paths();
        auto requests = convertJSON.get_requests();

        InvertedIndex invertedIndex;
        invertedIndex.update_freq_dict(file_paths);

        SearchEngine searchEngine(invertedIndex);
        searchEngine.set_response_limit(convertJSON.get_response_limit());
        auto answers = searchEngine.search(requests);

        std::vector<std::vector<std::pair<int, double>>> result;

        for (size_t i = 0; i < answers.size(); i++)
        {
            result.emplace_back();
            for (size_t j = 0; j < answers[i].size(); j++)
            {
                result[i].push_back({answers[i][j].doc_id, answers[i][j].rank});
            }
            
        }
        
        convertJSON.save_answers(result);
    }else {
        std::cout << convertJSON.get_error_msg();
        return 13;
    }
    
    return 0;
}