// 23k-0526

#include <iostream>
#include <cstring>
using namespace std;
class Document
{
    char *content;

public:
    Document(const char *initialContent)
    {
        if (initialContent)
        {
            content = new char[strlen(initialContent) + 1];
            strcpy(content, initialContent);
        }
        else
        {
            content = new char[1];
            content[0] = '\0';
        }
    }

    ~Document()
    {
        delete[] content;
    }

    Document(const Document &other)
    {
        content = new char[strlen(other.content) + 1];
        strcpy(content, other.content);
    }

    void display() const
    {
        cout << "Document Content: " << content << endl;
    }

    void setContent(const char *newContent)
    {
        delete[] content;

        content = new char[strlen(newContent) + 1];
        strcpy(content, newContent);
    }
    Document &operator=(const Document &other)
    {
        if (this == &other)
        {
            return *this;
        }
        delete[] content;
        content = new char[strlen(other.content) + 1];
        strcpy(this->content, other.content);

        return *this;
    }
};

int main()
{

    Document original("Initial Content");

    Document copy1 = original;

    original.setContent("Modified Content");

    cout << "-------------------------------------" << endl;
    cout << "Original Document: " << endl;
    original.display();

    cout << "Copy Document 1: " << endl;
    copy1.display();
    cout << "-------------------------------------" << endl;

    Document copy2("Temporary Content");
    copy2 = original;
    copy2.setContent("Content modified in copy 2");

    cout << "Original Document: " << endl;
    original.display();
    cout << "Copy Document 2: " << endl;
    copy2.display();
    cout << "-------------------------------------" << endl;

    return 0;
}
