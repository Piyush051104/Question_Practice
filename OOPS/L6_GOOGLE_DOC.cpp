#include <bits/stdc++.h>
using namespace std;
class DocumentElement{
    public:
    virtual string render() = 0;
};
class TextElement:public DocumentElement{
    public:
    string text;

    TextElement(string text){
        this->text = text;
    }

    string render() override{
        return text;
    }
};

class ImageElement : public DocumentElement{
    public:
    string text;

    ImageElement(string text){
        this->text = text;
    }
    string render(){
        return "Image" + text;
    }
};


class Document{
    public:
    vector<DocumentElement*>elements;

    void addelement(DocumentElement* ele){
        elements.push_back(ele);
    }

    string render(){
        string res = "";
        for(auto &i:elements){
            res += i->render();
        }
        return res;
    }
};

class persistnace{
    public:
    virtual void save(string res) = 0;
};

class SaveToFile : public persistnace{
    public:

    void save(string s){
        cout << "Save to file" << endl;
    }
};

class SaveToDB : public persistnace{
    public:

    void save(string s){
        cout << "Save to DB" << endl;
    }
};


class DocumentEditor{
    public:
    Document* document;
    persistnace* persist;
    string renderdoc;


    DocumentEditor(Document* document,persistnace* per){
        this -> document = document;
        this -> persist = per;
    }

    void addtext(string s){
        document->addelement(new TextElement(s));
    }

    void addimage(string s){
        document->addelement(new ImageElement(s));
    }

    

    string render(){
        if(renderdoc.empty()){
            renderdoc = document->render();
        }
        return renderdoc;
    }
    void save(){
        persist->save(render());
    }
};
int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    Document* doc = new Document();
    persistnace* per = new SaveToFile();

    DocumentEditor* editor = new DocumentEditor(doc,per);

    editor->addtext("Image");

    editor->addtext("Text");

    cout << editor -> render() << endl;

    editor->save();


    
}