--insert into supplier

insert into supplier values
(111 ,'supplier2' ,'road2 tel aviv' ,111111111 ),
(222 ,'supplier3' ,'road3 jerusalem' ,222222222 ),
(333 ,'supplier4' ,'road2 eilat' ,333333333 );
 
--insert into product

insert into product values
(987, 'Tomatoes', 'Vegetable', 'Kg', 5.99, 'manufacturer1', 111 ),
(876, 'Cucumbers' ,'Vegetable', 'Kg', 4.99, 'manufacturer2', 222), 
(765, 'Cornflakes', 'Cornflakes', 'Box', 15.9, 'manufacturer2', 222 ),
(654, 'Camembert' ,'Cheese', 'Box' ,12.50 ,'manufacturer2', 111 ),
(543, 'sweet potato', 'Vegetable', 'Kg', 16.40, 'manufacturer3', 333),
(432, 'red pepper' ,'Vegetable' ,'Kg', 15.99, 'manufacturer1', 111 );

--insert into branch

insert into branch values
(989 ,'tel aviv', 'road 1 tel aviv' ),
(878 ,'Raanana', 'road 2 raanana' ),
(767, 'Holon', 'road 3 holon' );

--insert into stock

insert into stock values
(987 ,989 ,50),
(987 ,878 ,75),
(987 ,767 ,100), 
(876 ,989 ,30),
(876 ,878 ,60),
(876 ,767 ,25),
(765 ,989 ,20) ,
(765 ,878 ,15),
(654 ,878 ,10) ,
(654 ,767 ,5) ,
(543 ,989 ,50) ,
(543 ,767 ,165) ,
(432 ,989 ,17) ,
(432 ,878 ,25) ,
(432 ,767 ,30);

--insert into receipt

insert into receipt values
(989 ,'2020.03.18','10:00','Cash' ,null ),
(989 ,'2020.07.16','12:30','Credit',null ), 
(989 ,'2020.7.15','15:35','Credit',null ),
(878 ,'2020.3.17','8:30','Cash',null ),
(878 ,'2020.7.22' ,'7:00','Credit', null),
(767 ,'2020.7.13' ,'22:00','Cash',null ),
(767 ,'2020.3.10' ,'20:30','Cash', null),
(767 ,'2020.5.14', '14:25','Credit', null);
 
--insert into purchase

insert into purchase values
(989 ,'2020.03.18','10:00' ,987 ,5),
(989 ,'2020.03.18','10:00' ,876 ,3) ,
(989 ,'2020.03.18','10:00' ,543 ,4) ,
(989 ,'2020.03.18' ,'10:00' ,432 ,1) ,
(878 ,'2020.3.17' ,'8:30' ,654 ,1) ,
(878 ,'2020.3.17' ,'8:30' ,432 ,3) ,
(767 ,'2020.3.10' ,'20:30' ,654 ,2) ,
(767 ,'2020.3.10' ,'20:30' ,987 ,3); 

