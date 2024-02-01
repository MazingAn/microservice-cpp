#! /usr/bin/python3

import sys

# load the cpp header file and generate the json converter code
header_file = sys.argv[1]
tvmap = {}
with open(header_file) as file:
    lines = file.readlines()
    for line in lines:
        if line.strip().split(" ")[0] in "int char* long std::string double float".split() :
            if(line.strip().split(" ")[1].endswith(";")):
                tname = line.split()[0];
                vname = line.split()[1][:-1];
                tvmap[vname] = tname

print("/*************** Start SerializeToJsonStr Code ********************/")
m2j_code = '''rapidjson::StringBuffer buffer;
rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
writer.StartObject();
'''
for v,t in tvmap.items():
    pv = v[0:-1] if v.endswith('_') else v
    m2j_code += "writer.String(\"{}\");\n".format(pv)
    if t == "char*":
        m2j_code += ("writer.String({});\n".format(v))
    elif t == "std::string":
        m2j_code += ("writer.String({}.c_str());\n".format(v))
    elif t == "long":
        m2j_code += ("writer.Int64({});\n".format(v))
    elif t == "int":
        m2j_code += ("writer.Int({});\n".format(v))
    elif t == "float":
        m2j_code += ("writer.Double({});\n".format(v))
    elif t == "double":
        m2j_code += ("writer.Double({});\n".format(v))
    else:
        pass
m2j_code += "writer.EndObject();\n"
m2j_code += "out_str = buffer.GetString();"
print(m2j_code)
print("/*************** End SerializeToJsonStr Code ********************/")
print("\n")
print("/************ Start DeSerializeFromJsonStr Code *****************/")
j2m_code='''rapidjson::Document document;
document.Parse(jsonStr.c_str());'''

for v,t in tvmap.items():
    pv = v[0:-1] if v.endswith('_') else v
    if t == "char*":
        j2m_code += "{} = document[\"{}\"].GetString();\n".format(v,pv);
    elif t == "std::string":
        j2m_code += "{} = document[\"{}\"].GetString();\n".format(v,pv);
    elif t == "long":
        j2m_code += "{} = document[\"{}\"].GetInt64();\n".format(v,pv);
    elif t == "int":
        j2m_code += "{} = document[\"{}\"].GetInt();\n".format(v,pv);
    elif t == "float":
        j2m_code += "{} = static_cast<float>(document[\"{}\"].GetDouble());\n".format(v,pv);
    elif t == "double":
        j2m_code += "{} = document[\"{}\"].GetDouble();\n".format(v,pv);
    else:
        pass
print(j2m_code)
print("/************ End DeSerializeFromJsonStr Code *****************/")
