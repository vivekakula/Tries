#include <iostream>
using namespace std;

const int ALPHABET_SIZE = 26;

struct Trie
{
    /* data */
    struct Trie* children[ALPHABET_SIZE];
    //flag to mark the end of word
    bool isEndofWord;
};

//Create new node
struct Trie* getNode()
{
    struct Trie* node = new Trie;

    node->isEndofWord = false;
    for(int i=0;i<ALPHABET_SIZE;++i)
    {
        node->children[i] = nullptr;
    }
    return node;
}

//insert the string into the trie
void insert(struct Trie* root, string key)
{
    struct Trie* node = root;
    
    for(int i=0; i< key.length(); ++i)
    {
        int index = key[i] - 'a'; // Calculating the index of the letter in string
        if(!node->children[index]) // If the value at the indexx is null
            node->children[index] = getNode(); // generate new node
        
        //if the value at the index is not zero we can move the node to that index for next letter
        node = node->children[index];
    }
    node -> isEndofWord = true; //after the word end mark the flag as end
    cout << "inserted :: " << key << endl;
}

//Serach method
bool search(struct Trie* root, string searchKey)
{
    struct Trie* node = root;

    for(int i=0; i<searchKey.length(); ++i)
    {
        int index = searchKey[i] - 'a';
        if(!node->children[index])
            return false;
        
        node = node->children[index];
    }
    // Check last letter is not null and it is end of the word
    return (node!=nullptr && node->isEndofWord);
}

// isEmpty Utility for checking the root node
bool isEmpty(struct Trie * root)
{
    for(int i=0; i< ALPHABET_SIZE; i++)
    {
        //Checking if the value is present in the children node if present it is not empty
        if(root->children[i]) 
            return false;
    }
    return true;
}

//remove entry from the trie - using recursion to remove the entry in the trie
Trie* remove(struct Trie* root, string removalString, int depth =0)
{
    // base condition
    if(!root)
        return nullptr;

    //depth holds the size of the keys processed
    //if last character is being processed
    if(depth == removalString.size())
    {
        //If the end of word is set unset it
        if(root->isEndofWord)
            root->isEndofWord = false;
        
        //now check if the root at this level dont have any children
        //if there are no children we can remove the root and mark the root as NULL
        if(isEmpty(root))
        {
            delete root;
            root = nullptr;
        }

        return root;
    }

    //If not last character do recursion for the rest of the keys in the string
    int index = removalString[depth]-'a';
    root->children[index]=remove(root->children[index],removalString,depth+1);

    //If root does not have any more childs ( the child get deleted via recusrion)
    //and it is not end of another word.
    if(isEmpty(root) && root->isEndofWord ==false)
    {
        delete root;
        root = nullptr;
    }

    return root;
}

//Driver Code
int main()
{

    string keys[] = { "the", "a", "there",
                      "answer", "any", "by",
                      "bye", "their", "hero", "heroplane" };
    int n = sizeof(keys) / sizeof(keys[0]);
 
    struct Trie* root = getNode();
 
    // Construct trie
    for (int i = 0; i < n; i++)
    {
        insert(root, keys[i]);
    }
    // Search for different keys
    search(root, "the") ? cout << "Yes\n" : cout << "No\n";
    search(root, "these") ? cout << "Yes\n" : cout << "No\n";
 
    remove(root, "heroplane");
    search(root, "hero") ? cout << "Yes\n" : cout << "No\n";
    return 0;

}

