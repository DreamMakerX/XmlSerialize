#include "XmlSerializer.h"

class Grade {
public:
    std::string courseName;
    std::string teacherName;
    int score;

    void toXml(XMLElement* elem) const {
        XmlSerializer::writeElement(elem, "CourseName", courseName);
        XmlSerializer::writeElement(elem, "TeacherName", teacherName);
        XmlSerializer::writeElement(elem, "Score", score);
    }

    void fromXml(XMLElement* elem) {
        XmlSerializer::readElement(elem, "CourseName", courseName);
        XmlSerializer::readElement(elem, "TeacherName", teacherName);
        XmlSerializer::readElement(elem, "Score", score);
    }
};
class Student {
public:
    std::string name;
    int id;
    std::vector<Grade> grades;

    void toXml(XMLElement* elem) const {
        XmlSerializer::writeElement(elem, "Name", name);
        XmlSerializer::writeElement(elem, "Id", id);
        XmlSerializer::writeElementArray(elem, "Grades", grades);
    }

    void fromXml(XMLElement* elem) {
        XmlSerializer::readElement(elem, "Name", name);
        XmlSerializer::readElement(elem, "Id", id);
        XmlSerializer::readElementArray(elem, "Grades", grades);
    }
};

std::string GetXmlString()
{
    return "<Root><Name>zcc</Name><Id>4078</Id><Grades><Item><CourseName>Math</CourseName><TeacherName>bo.wang</TeacherName><Score>95</Score></Item><Item><CourseName>Physics</CourseName><TeacherName>dingtai.tang</TeacherName><Score>100</Score></Item></Grades></Root>";
/*XML文件格式
<Root>
    <Name>zcc</Name>
    <Id>4078</Id>
    <Grades>
        <Item>
            <CourseName>Math</CourseName>
            <TeacherName>bo.wang</TeacherName>
            <Score>95</Score>
        </Item>
        <Item>
            <CourseName>Physics</CourseName>
            <TeacherName>dingtai.tang</TeacherName>
            <Score>100</Score>
        </Item>
    </Grades>
</Root>
*/
}
void PrintStudentObject(const Student& student)
{
    std::cout << "====================print student object start====================" << std::endl;
    std::cout << "Deserialized Student:" << std::endl;
    std::cout << "Name: " << student.name << std::endl;
    std::cout << "ID: " << student.id << std::endl;
    std::cout << "Grades:" << std::endl;
    for (const Grade& grade : student.grades) {
        std::cout << "Course Name: " << grade.courseName << std::endl;
        std::cout << "Teacher Name: " << grade.teacherName << std::endl;
        std::cout << "Score: " << grade.score << std::endl;
        std::cout << std::endl;
    }
    std::cout << "====================print student object end======================" << std::endl;
}
void PrintXmlString(const std::string& xml)
{
    std::cout << "====================print xml string start========================" << std::endl;
    std::cout << xml << std::endl;
    std::cout << "====================print xml string end==========================" << std::endl;
}

void main() {

    //执行反序列化
    Student student;
    XmlSerializer::Deserialize(GetXmlString(), student);

    //遍历输出Student对象
    PrintStudentObject(student);

    //任意修改对象属性，以id为例
    student.id = 363258;

    //执行序列化
    std::string xml = XmlSerializer::Serialize(student);

    //输出序列化结果
    PrintXmlString(xml);

    std::cin.get();
}
