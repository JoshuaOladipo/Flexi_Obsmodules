%Script to perform reduced link load approximation for an OBS network
clear;
clc;
routes = [2,1,0,0;1,2,3,0;6,7,0,0;7,2,0,0;3,2,0,0;5,6,0,0];
num_links = 7;
num_waves = 6;
route_arr_rate = 55.64; %burst/secs
avg_burst_length = 13527; %Bytes
channel_speed = 10000000000;%bits per sec
node_processing_time =0.0005; %secs
channel_service_time = (avg_burst_length*8)/channel_speed; %secs
avg_node_count = [1,0.5,0.5,0,1,0.5,0.5]; %average node count at a link
add_mask = (avg_node_count > 0) *0.00005;
mean_route_offsets = (node_processing_time*avg_node_count)+add_mask; %per link
mu_j = num_waves ./(mean_route_offsets + channel_service_time);
rho_j = ones(num_links,1);

B_j = ones(num_links, 1);
B_j1 = zeros(num_links,1);

counter = 0;
 while max(abs(B_j - B_j1)) > 0.00001
     counter = counter+1;
   for i =1:num_links
     B_j(i) = B_j1(i);
     for j = 1:num_links
       sum =0;
       
       for k = 1:size(routes,2)
         prod = 1;
         for l=1:num_links
           prod = prod * (1 - (I(l,j,k,routes)*B_j(l)));
         end
         sum = sum+prod;
       end
   
    rho_j(j) = route_arr_rate*(mu_j(j)^(-1))*sum;
    end
 
   B_j1(i) = rho_j(i)/(1 + rho_j(i))
   end
 end

route_blocking = ones(size(routes,1));

for i=1:size(routes,1)
    prod2 = 1;
    for j = 1:size(routes,2)
        if(routes(i,j) > 0)
        prod2 = prod2 * (1-B_j1(routes(i,j)));
        end
    end
     
    route_blocking(i) = route_blocking(i) - prod2;
end

burst_blocking = route_arr_rate/(route_arr_rate*size(routes,1))
sum2 =0;

for i=1:size(route_blocking,1)
   sum2 = sum2 +  route_blocking(i); 
end

burst_blocking = burst_blocking*sum2 % final result