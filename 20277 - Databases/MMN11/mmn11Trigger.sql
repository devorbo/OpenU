create or replace function trigf1() returns trigger as $$
declare
quantity float;
price float;
totalPrice float;
begin
		update receipt 
		set total=0
		where total is null;
		
		select s.units into quantity from stock s where s.bid=new.bid and s.code=new.code;
		if new.units>quantity
		then
			begin
				new.units:=0;
				raise notice 'messing units in stock';
			end;
		else
			begin
				update stock 
				set units=units-new.units
				where bid=new.bid; 
				
				select pr.uprice into price from product pr
				where pr.code=new.code;
				
				totalPrice:=price*new.units;
				
				update receipt 
				set total=total+totalPrice
				where bid=new.bid and rdate=new.rdate and rtime=new.rtime;
			end;
		end if;
		return new;
end;$$LANGUAGE plpgsql;

create trigger T1
before insert on purchase
for each row
execute procedure trigf1();
