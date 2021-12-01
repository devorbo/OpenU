
--1
select p.code,p.pname
from product p
where p.manu='manufacturer2' and p.uprice>10;

--2
select p.pname,s.sname
from product p, supplier s
where p.sid=s.sid and 
		p.descr='Vegetable' and p.utype='Kg' and p.uprice>15;
		
--3
select p.bid
from purchase p
where date_part('month',p.rdate)=
	 date_part('month',current_date) and 
	 date_part('year',p.rdate)=
	 date_part('year',current_date)
group by p.bid
having count(p.bid)<3;

--4
select s.sname, p1.pname
from supplier s,product p1
where s.sid=p1.sid and s.sid=(
	select p.sid
	from product p
	group by(p.sid)
	having count(p.sid)=1);

--5
with total_for_branch(bid,totalSum) as(
select pu.bid as id,sum(pu.units*pr.uprice) as totalSum
from product pr,purchase pu
where pr.code=pu.code
group by pu.bid)

select t.bid, b.bname
from total_for_branch t,branch b
where b.bid=t.bid and t.totalSum>=all(select totalSum
					from total_for_branch);
					
--6
select temp.bid
from
	(select s.bid,count(*)
	from stock s
	group by s.bid) as temp
where temp.count=(select count(*) from product);

--7

--num suppliers for purchase without cucumbers		
with count_sid_for_receipt(bid,rdate,rtime,countsid) as (
			select pu.bid, pu.rdate,pu.rtime, count(distinct pr.sid) as countSid
			from purchase pu,product pr,
									(--purchase without cucumbers		
									select pu.bid, pu.rdate,pu.rtime
									from purchase pu
									except
									select pu.bid, pu.rdate,pu.rtime
									from purchase pu
									where pu.code=(select code from product where pname='Cucumbers')) as temp
			where pr.code=pu.code and pu.bid=temp.bid and pu.rdate=temp.rdate and pu.rtime=temp.rtime
			group by pu.bid, pu.rdate,pu.rtime)	
--min supplier for total above 50				
select co.bid, co.rdate,co.rtime
from count_sid_for_receipt co, receipt r
where countSid<=all(select countSid from count_sid_for_receipt)
and co.bid=r.bid and co.rdate=r.rdate and co.rtime=r.rtime and r.total>50;
			