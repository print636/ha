
class Useer():

    def __init__(self,first_name,last_name,age,sex,phone):
        self.first_name = first_name
        self.last_name = last_name
        self.age = age
        self.sex = sex
        self.phone = phone

    def describe_user(self):
        print('大家好我叫%s %s,我今年%d岁，我的电话是%s'%(self.first_name,self.last_name,self.age,self.phone))

    def greet_user(self):
        print('尊敬的%s，恭喜你中了500万！'%self.first_name)
    
if __name__ == '__main__':

    joe = Useer('joe','black',18,'男','13811111111')
    joe.describe_user()
    joe.greet_user()