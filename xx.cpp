class ClassRoom {
private:
    vector<string> students;

public:
    ClassRoom(vector<string>&& theStudents)
        :students{std::forward<vector<string>>(theStudents)}
    {

    }

};

class ClassRoom {
private:
    vector<string> students;

public:
    ClassRoom(vector<string>&& theStudents)
        :students{std::move(theStudents)}
    {

    }

};
