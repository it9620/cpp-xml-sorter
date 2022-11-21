#include "../lib/pugixml-1.13/src/pugixml.hpp"
#include <iostream>
//#include <algorithm>
#include <string>
#include <map>
#include <vector>

#define UNUSED(expr) do { (void)(expr); } while (0)

using namespace std;

bool XMLNodeIndexComp(pugi::xml_named_node_iterator lhs, pugi::xml_named_node_iterator rhs) {
    pugi::xml_node lhs_index_node = lhs->child("Index");
        pugi::xml_node rhs_index_node = rhs->child("Index");
        if (!lhs_index_node || !rhs_index_node) {
            return false;
        }
        return stoi(lhs_index_node.child_value()) < stoi(rhs_index_node.child_value());
}

int main()
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(
        "/Users/maymac2/vscode/CppXMLSorter/files/input/witsmlTable.xml");
    if (!result)
        return -1;

    auto array_of_chanel = doc.child("ArrayOfChannel");
    auto chldrn = array_of_chanel.children("Channel");

    vector<string> array_atributes_names;
    vector<string> array_atributes;
    for (const auto& atribute : array_of_chanel.attributes()) {
        array_atributes_names.push_back(atribute.name());
        array_atributes.push_back(atribute.as_string());        
    }

    //pugi::sort(chldrn.begin(), chldrn.end(), XMLNodeIndexComp);
    /*pugi::sort(chldrn.begin(), chldrn.end(), [](auto& lhs, auto& rhs) {
        //return (lhs.child("Index")) < (rhs.child("Index"));
        pugi::xml_node lhs_index_node = lhs.child("Index");
        pugi::xml_node rhs_index_node = rhs.child("Index");
        if (!lhs_index_node || !rhs_index_node) {
            return false;
        }
        return stoi(lhs_index_node.child_value()) < stoi(rhs_index_node.child_value());
    });*/

    map<int, pugi::xml_named_node_iterator> sorted_xml;
    auto it = chldrn.begin();
    while (it != chldrn.end()) {
        pugi::xml_node index_node = it->child("Index");
        string index_str = index_node.child_value();
        int index_val = stoi (index_str);
        sorted_xml[index_val] = it;
        ++it;
    } // */
    cout << "Map created." << endl;

    //===================================================================================
    // Work to save modified XML file.
    
    pugi::xml_document result_doc;
    result_doc.append_child("ArrayOfChannel");

    pugi::xml_node result_array_of_chanel = result_doc.child("ArrayOfChannel");

    for (int i = 0; i < array_atributes.size(); ++i) {
        string str_name = array_atributes_names.at(i);
        //pugi::char_t* name;

        //result_array_of_chanel.append_attribute(name);

        string str_atribute = array_atributes.at(i);
        pugi::xml_attribute atribute;
        atribute.set_name(str_name.c_str());
        atribute.set_value(str_atribute.c_str());

        //result_array_of_chanel.append_attribute(atribute);

        //atribute = str_atribute;
        result_array_of_chanel.attribute(str_name.c_str()).set_value(atribute);
    }
    
    result_array_of_chanel.append_child("Chanel");
    //result_array_of_chanel.set_name("ArrayOfChannel");
    
    for (const auto& [index, node] : sorted_xml) {
        pugi::xml_node tmp_node = *node;
        //result_array_of_chanel.insert_child_after("Chanel", tmp_node);
        result_array_of_chanel.append_copy(tmp_node);
        //result_array_of_chanel.append_child("Chanel", tmp_node);
    }
    //result_doc.insert_child_after("ArrayOfChannel",result_array_of_chanel);

    result_doc.save_file("/Users/maymac2/vscode/CppXMLSorter/files/output/result.xml");


    cout << "Programm end." << endl;

    return 0;
}