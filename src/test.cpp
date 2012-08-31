#include "test.hpp"

using namespace std;
using namespace mongo;
using namespace bson;

void test_mongodb(int argc, char* argv[])
{
    try
    {
        DBClientConnection c;
        c.connect("localhost");
        cout << "connected ok" << endl;
        BSONObjBuilder b;
        b << "name" << "Joe" << "age" << 33;
        BSONObj p = b.obj();

        const string dbname = "test.db";

        c.insert(dbname, p);

        cout << "count:" << c.count(dbname) << endl;

        auto_ptr<DBClientCursor> cursor = c.query(dbname, BSONObj());
        while (cursor->more())
            cout << cursor->next().toString() << endl;

        BSONObjBuilder bbuilder;
        bbuilder << "imgName" << "1.jpg";

        BSONArrayBuilder abuilder;
        for (int i = 0; i < 4; ++i)
            abuilder << 2 * i;
        BSONArray barray = abuilder.arr();

        bbuilder << "part" << barray;

        bo an_obj = bbuilder.obj();

        cout << an_obj["imgName"] << " ";
        vector<be> v_be = an_obj["part"].Array();
        for (int i = 0; i < v_be.size(); ++i)
        {
            cout << v_be[i].Int() << " ";

        }

        c.insert(dbname, an_obj);

        c.update(dbname, p, BSON("name"<<"jie"<<"age"<<22));

        cursor = c.query(dbname, BSONObj());
        while (cursor->more())
            cout << cursor->next().toString() << endl;

    }
    catch (DBException &e)
    {
        cout << "caught " << e.what() << endl;
    }

}
