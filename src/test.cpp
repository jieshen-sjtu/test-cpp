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

        const string dbname = "test.db2";

        /*c.insert(dbname, p);

        //cout << "count:" << c.count(dbname) << endl;

        auto_ptr<DBClientCursor> cursor = c.query(dbname, BSONObj());
        while (cursor->more())
            cout << cursor->next().toString() << endl;*/

        BSONObjBuilder bbuilder;
        bbuilder << "imgName" << "1.jpg";

        BSONArrayBuilder abuilder;
        for (int i = 0; i < 4; ++i)
        {
            BSONObjBuilder tmp;
            tmp << "torso" << i;
            abuilder << tmp.obj();
        }
        BSONObj barray = abuilder.obj();

        bbuilder << "part" << barray;

        bo an_obj = bbuilder.obj();

        /*cout << an_obj["imgName"] << " ";
        vector<be> v_be = an_obj["part"].Array();
        for (int i = 0; i < v_be.size(); ++i)
        {
            cout << v_be[i].Int() << " ";

        }*/

        //c.insert(dbname, an_obj);

        c.update(dbname, p, BSON("name"<<"jie"<<"age"<<22));

        auto_ptr<DBClientCursor> cursor = c.query(dbname,QUERY("imgName"<<"1.jpg"));
        /*while (cursor->more())
            cout << cursor->next().toString() << endl;*/
        if(cursor->more())
            {
            cout << "find 1.jpg" <<endl;
            cout << cursor->next().toString() << endl;
            }
        else
        {
            cout << "not find" <<endl;
        }

        cursor = c.query(dbname,QUERY("imgName"<<"2.jpg"));
        if(cursor->more())
        {
            cout << "find 2.jpg" << endl;
            cout << cursor->next().toString() <<endl;
        }
        else
        {
            cout <<" insert 2.jpg" <<endl;
        }

    }
    catch (DBException &e)
    {
        cout << "caught " << e.what() << endl;
    }

}
