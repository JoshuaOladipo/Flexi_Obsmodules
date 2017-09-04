 function [y] = I(i,j,r,routes)
   y = 0;
   index_j = find(routes(r,:)==j);%determine if j in r
   if(index_j > 1)  %check if index of i < index of j in r
     index_i = find(routes(r,:)==i);
     
     if(~isempty(index_i) && index_i < index_j)
     y = 1;
     end
   end
   
   return
   end