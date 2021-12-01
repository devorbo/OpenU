drop table purchase;
drop table receipt;
drop table stock;
drop table branch;
drop table product;
drop table supplier;

create table Supplier(
sid int,
sname varchar(30),
address varchar(50),
phone numeric(9,0),
primary key(sid));

create table Product(
code int,
pname varchar(30),
descr varchar(50),
utype varchar(30),
uprice float,
manu varchar(30),
sid int,
primary key(code),
foreign key(sid) references supplier);

create table Branch(
bid int,
bname varchar(30),
baddress varchar(50),
primary key(bid));

create table Stock(
code int,
bid int,
units float,
primary key(code,bid),
foreign key(code) references product,
foreign key(bid) references branch);

create table Receipt(
bid int,
rdate date,
rtime time,
ptype varchar(30),
total float default 0,
primary key(bid, rdate, rtime),
foreign key(bid) references branch);

create table Purchase(
bid int,
rdate date,
rtime time,
code int,
units float ,
primary key(bid, rdate, rtime,code),
foreign key(bid, rdate, rtime) references receipt,
foreign key(code) references product);
