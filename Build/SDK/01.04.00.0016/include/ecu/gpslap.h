#ifndef __ECU_GPSLAP_H__
#define __ECU_GPSLAP_H__

#include <ecu/types.h>

/**
 * @addtogroup GPSLap
 * @{
 */

extern s32 gpslap_number;
extern u32 gpslap_ticks;

/**
 * @fn bool gpslap_init(f32 radius, s32e7 lat1, s32e7 lon1, s32 bn1, s32e7 lat2, s32e7 lon2, s32 bn2, s32e7 lat3, s32e7 lon3, s32 bn3, s32e7 lat4, s32e7 lon4, s32 bn4)
 * @arg ScriptName Init
 *
 * @brief Initialise GPS lap calculation.
 *
 * @details <p>Initialises the GPS lap calculation system.</p>
 * @details <p>Up to four custom GPS beacon locations can be specified.</p>
 * @details <p>A beacon is generated when the GPS coordinates passed to the
 * @details GPS.Calculate function follow a path through a detection circle
 * @details defined by the beacon coordinates and the <span class="param"/>radius
 * @details </span> parameter.</p>
 * @details <p>The following locations are automatically detected by the system:
 * @details <table class=param>
 * @details <tr><th>Name</th><th>Beacon Number</th><th>Latitude</th><th>Longitude</th></tr>
 * @details <!-- INSERT_VENUES_HERE -->
 * @details <tr><td>A1-Ring</td><td>100</td><td>47.2197720</td><td>14.7642950</td></tr>
 * @details <tr><td>Adelaide</td><td>200</td><td>-34.9303800</td><td>138.6204960</td></tr>
 * @details <tr><td>Adirondack Intl</td><td>300</td><td>43.8532840</td><td>-75.4531790</td></tr>
 * @details <tr><td>Ahvenisto</td><td>400</td><td>61.0037342</td><td>24.4179526</td></tr>
 * @details <tr><td>Akron</td><td>500</td><td>41.0511530</td><td>-81.4677140</td></tr>
 * @details <tr><td>Alastaro</td><td>600</td><td>60.9762265</td><td>22.6580859</td></tr>
 * @details <tr><td>Albacete</td><td>700</td><td>39.0051590</td><td>-1.7956130</td></tr>
 * @details <tr><td>Albert Park</td><td>800</td><td>-37.8499733</td><td>144.9688260</td></tr>
 * @details <tr><td>Aldo Scribante</td><td>900</td><td>-33.8068210</td><td>25.6458930</td></tr>
 * @details <tr><td>Anderstorp</td><td>1000</td><td>57.2615090</td><td>13.5993440</td></tr>
 * @details <tr><td>Arizona Motorsports Park</td><td>1100</td><td>33.5168610</td><td>-112.3917970</td></tr>
 * @details <tr><td>Arroyo Seco</td><td>1200</td><td>32.2368390</td><td>-107.4296810</td></tr>
 * @details <tr><td>Aspen</td><td>1300</td><td>39.2664170</td><td>-106.8800400</td></tr>
 * @details <tr><td>Assen</td><td>1400</td><td>52.9629295</td><td>6.5252761</td></tr>
 * @details <tr><td>Atlanta Dragway</td><td>1500</td><td>34.2637380</td><td>-83.4724550</td></tr>
 * @details <tr><td>Atlanta MS Oval</td><td>1600</td><td>33.3857699</td><td>-84.3168950</td></tr>
 * @details <tr><td>Autobahn Full</td><td>1700</td><td>41.4565580</td><td>-88.1258950</td></tr>
 * @details <tr><td>Autobahn South</td><td>1800</td><td>41.4552110</td><td>-88.1268740</td></tr>
 * @details <tr><td>Autodromo Hermanos Rodriguez</td><td>1900</td><td>19.4061460</td><td>-99.0928360</td></tr>
 * @details <tr><td>Autodromo Miguel E Abed</td><td>2000</td><td>19.0278440</td><td>-97.9896680</td></tr>
 * @details <tr><td>Autopolis</td><td>2100</td><td>33.0374520</td><td>130.9751660</td></tr>
 * @details <tr><td>Bahia Blanca</td><td>2200</td><td>-38.6816870</td><td>-62.1770650</td></tr>
 * @details <tr><td>Balcarce</td><td>2300</td><td>-37.8829620</td><td>-58.2666970</td></tr>
 * @details <tr><td>Barbagallo</td><td>2400</td><td>-31.6641775</td><td>115.7863923</td></tr>
 * @details <tr><td>Barber</td><td>2500</td><td>33.5326919</td><td>-86.6195130</td></tr>
 * @details <tr><td>Barcelona</td><td>2600</td><td>41.5699610</td><td>-2.2609611</td></tr>
 * @details <tr><td>Baskerville</td><td>2700</td><td>-42.7464370</td><td>147.2943970</td></tr>
 * @details <tr><td>Bathurst</td><td>2800</td><td>-33.4393834</td><td>149.5592218</td></tr>
 * @details <tr><td>BeaveRun</td><td>2900</td><td>40.8507250</td><td>-80.3477690</td></tr>
 * @details <tr><td>Bedford</td><td>3000</td><td>52.2351350</td><td>0.4743260</td></tr>
 * @details <tr><td>Berlin</td><td>3100</td><td>43.0359680</td><td>-85.8347330</td></tr>
 * @details <tr><td>Bira</td><td>3200</td><td>12.9207095</td><td>101.0085273</td></tr>
 * @details <tr><td>Black Hawk</td><td>3300</td><td>42.4878850</td><td>-89.1174780</td></tr>
 * @details <tr><td>Blue Grass</td><td>3400</td><td>38.7646750</td><td>-84.8035200</td></tr>
 * @details <tr><td>Botnia</td><td>3500</td><td>62.6244026</td><td>22.0152028</td></tr>
 * @details <tr><td>Brainerd</td><td>3600</td><td>46.4168620</td><td>-94.2748079</td></tr>
 * @details <tr><td>Brands Hatch</td><td>3700</td><td>51.3602527</td><td>0.2599997</td></tr>
 * @details <tr><td>Brasilia</td><td>3800</td><td>-15.7728170</td><td>-47.9002510</td></tr>
 * @details <tr><td>Brimley</td><td>3900</td><td>46.3712650</td><td>-84.5759870</td></tr>
 * @details <tr><td>Bristol</td><td>4000</td><td>36.5159960</td><td>-82.2561680</td></tr>
 * @details <tr><td>Brno</td><td>4100</td><td>49.2032263</td><td>16.4439615</td></tr>
 * @details <tr><td>Broadford</td><td>4200</td><td>-37.2159070</td><td>145.0823480</td></tr>
 * @details <tr><td>Buenos Aires</td><td>4300</td><td>-34.6942270</td><td>-58.4613890</td></tr>
 * @details <tr><td>Bushy Park</td><td>4400</td><td>13.1386780</td><td>-59.4669970</td></tr>
 * @details <tr><td>Buttonwillow</td><td>4500</td><td>35.4887330</td><td>-119.5444720</td></tr>
 * @details <tr><td>Cadwell Park</td><td>4600</td><td>53.3107205</td><td>0.0591005</td></tr>
 * @details <tr><td>Calabogie</td><td>4700</td><td>45.3017350</td><td>-76.6723610</td></tr>
 * @details <tr><td>Calder</td><td>4900</td><td>-37.6709228</td><td>144.7538686</td></tr>
 * @details <tr><td>Calder Oval</td><td>4800</td><td>-37.6730540</td><td>144.7600010</td></tr>
 * @details <tr><td>California Speedway</td><td>5000</td><td>34.0860690</td><td>-117.5005250</td></tr>
 * @details <tr><td>Campo Grande</td><td>5100</td><td>-20.4759110</td><td>-54.4660250</td></tr>
 * @details <tr><td>Carolina Motorsports</td><td>5200</td><td>34.4877270</td><td>-80.5970040</td></tr>
 * @details <tr><td>Cartagena</td><td>5300</td><td>37.6451000</td><td>-1.0357850</td></tr>
 * @details <tr><td>Cascavel</td><td>5400</td><td>-24.9805930</td><td>-53.3827290</td></tr>
 * @details <tr><td>Castle Combe</td><td>5500</td><td>51.4927370</td><td>-2.2160250</td></tr>
 * @details <tr><td>Catalunya</td><td>5600</td><td>41.5700299</td><td>2.2612160</td></tr>
 * @details <tr><td>Chicagoland</td><td>5700</td><td>41.4731321</td><td>-88.0598750</td></tr>
 * @details <tr><td>Chimay</td><td>5800</td><td>50.0553100</td><td>4.3039960</td></tr>
 * @details <tr><td>Chuckwalla Valley</td><td>5900</td><td>33.7938560</td><td>-115.2960520</td></tr>
 * @details <tr><td>Circuit Gilles Villeneuve</td><td>6000</td><td>45.5000550</td><td>-73.5227050</td></tr>
 * @details <tr><td>Circuit Mont-Tremblant</td><td>6100</td><td>46.1933190</td><td>-74.6116410</td></tr>
 * @details <tr><td>Circuito del Jarama</td><td>6200</td><td>40.6146530</td><td>-3.5831600</td></tr>
 * @details <tr><td>Comodoro Rivadavia</td><td>6300</td><td>-45.9027350</td><td>-67.5439019</td></tr>
 * @details <tr><td>Concordia</td><td>6400</td><td>-31.3084410</td><td>-58.0038170</td></tr>
 * @details <tr><td>Consumer Union Track</td><td>6500</td><td>41.5240400</td><td>-72.3598170</td></tr>
 * @details <tr><td>Croft</td><td>6600</td><td>54.4555111</td><td>-1.5555266</td></tr>
 * @details <tr><td>Darlington</td><td>6700</td><td>34.2936990</td><td>-79.9060540</td></tr>
 * @details <tr><td>Darwin</td><td>6800</td><td>-12.4483680</td><td>130.9077400</td></tr>
 * @details <tr><td>Daytona</td><td>6900</td><td>29.1876670</td><td>-81.0727830</td></tr>
 * @details <tr><td>Dijon</td><td>7000</td><td>47.3635499</td><td>4.8981333</td></tr>
 * @details <tr><td>Donington Park</td><td>7100</td><td>52.8297521</td><td>-1.3784046</td></tr>
 * @details <tr><td>Dover</td><td>7200</td><td>39.1907590</td><td>-75.5287470</td></tr>
 * @details <tr><td>Dubai</td><td>7300</td><td>25.0474250</td><td>55.2395810</td></tr>
 * @details <tr><td>Eagles Canyon</td><td>7400</td><td>33.3676120</td><td>-97.4296720</td></tr>
 * @details <tr><td>Eastern Creek</td><td>7500</td><td>-33.8037274</td><td>150.8708936</td></tr>
 * @details <tr><td>Estoril</td><td>7600</td><td>38.7494170</td><td>-9.3929060</td></tr>
 * @details <tr><td>Evergreen</td><td>7700</td><td>47.8692300</td><td>-121.9883590</td></tr>
 * @details <tr><td>Firebird East</td><td>7800</td><td>33.2737759</td><td>-111.9633330</td></tr>
 * @details <tr><td>Firebird Intl</td><td>7900</td><td>33.2675260</td><td>-111.9681430</td></tr>
 * @details <tr><td>Firebird West</td><td>8000</td><td>33.2689140</td><td>-111.9719700</td></tr>
 * @details <tr><td>Ford Test Track</td><td>8100</td><td>42.2983789</td><td>-83.2259279</td></tr>
 * @details <tr><td>Fortaleza</td><td>8200</td><td>-3.8823340</td><td>-38.4587900</td></tr>
 * @details <tr><td>Fuji</td><td>8300</td><td>35.3738250</td><td>138.9297369</td></tr>
 * @details <tr><td>Fundidora Park</td><td>8400</td><td>25.6778010</td><td>-100.2864750</td></tr>
 * @details <tr><td>Gainsville</td><td>8500</td><td>28.1514520</td><td>-81.8913010</td></tr>
 * @details <tr><td>Gateway Intl</td><td>8600</td><td>38.6504510</td><td>-90.1369110</td></tr>
 * @details <tr><td>Gellerasen</td><td>8700</td><td>59.3832120</td><td>14.5136690</td></tr>
 * @details <tr><td>General Roca</td><td>8800</td><td>-39.0764090</td><td>-67.5804130</td></tr>
 * @details <tr><td>Gingerman</td><td>8900</td><td>42.4080390</td><td>-86.1404619</td></tr>
 * @details <tr><td>Goiania</td><td>9000</td><td>-16.7193990</td><td>-49.1930290</td></tr>
 * @details <tr><td>Goodwood</td><td>9100</td><td>50.8579560</td><td>0.7526280</td></tr>
 * @details <tr><td>GrandSport Speedway</td><td>9200</td><td>29.3247230</td><td>-95.0462830</td></tr>
 * @details <tr><td>Grattan</td><td>9300</td><td>43.0960670</td><td>-85.3843530</td></tr>
 * @details <tr><td>Guapore</td><td>9400</td><td>-28.8445610</td><td>-51.8526390</td></tr>
 * @details <tr><td>Hallett</td><td>9500</td><td>36.2206780</td><td>-96.5903970</td></tr>
 * @details <tr><td>Harris Hill</td><td>9600</td><td>29.9188960</td><td>-97.8732120</td></tr>
 * @details <tr><td>Heartland</td><td>9700</td><td>38.9269460</td><td>-95.6767240</td></tr>
 * @details <tr><td>High Plains</td><td>9800</td><td>39.7349470</td><td>-103.8939710</td></tr>
 * @details <tr><td>Holden Performance</td><td>9900</td><td>-27.7469180</td><td>153.2936230</td></tr>
 * @details <tr><td>Homebush</td><td>10000</td><td>-33.8437200</td><td>151.0708090</td></tr>
 * @details <tr><td>Homestead</td><td>10100</td><td>25.4537139</td><td>-80.4097170</td></tr>
 * @details <tr><td>Honda Proving Center</td><td>10200</td><td>35.2604080</td><td>-117.9589710</td></tr>
 * @details <tr><td>Hungaroring</td><td>10300</td><td>47.5788830</td><td>19.2484140</td></tr>
 * @details <tr><td>Imola</td><td>10400</td><td>44.3440293</td><td>11.7163993</td></tr>
 * @details <tr><td>Indianapolis</td><td>10600</td><td>39.7931470</td><td>-86.2389000</td></tr>
 * @details <tr><td>Indianapolis MS</td><td>10500</td><td>39.7931490</td><td>-86.2388700</td></tr>
 * @details <tr><td>Infineon</td><td>10700</td><td>38.1615848</td><td>-122.4547235</td></tr>
 * @details <tr><td>Interlagos GP Circuit</td><td>10800</td><td>-23.7040320</td><td>-46.6998710</td></tr>
 * @details <tr><td>Interlomas</td><td>10900</td><td>-38.6207310</td><td>-72.4670270</td></tr>
 * @details <tr><td>Irwindale</td><td>11000</td><td>34.1109899</td><td>-117.9875460</td></tr>
 * @details <tr><td>Jerez</td><td>11100</td><td>36.7096740</td><td>-6.0324950</td></tr>
 * @details <tr><td>Johor</td><td>11200</td><td>1.4800850</td><td>103.9083349</td></tr>
 * @details <tr><td>Kaeng Krachan</td><td>11300</td><td>12.9453232</td><td>99.7061944</td></tr>
 * @details <tr><td>Kansas Speedway</td><td>11400</td><td>39.1165810</td><td>-94.8338380</td></tr>
 * @details <tr><td>Kemora</td><td>11500</td><td>63.4202520</td><td>23.9832492</td></tr>
 * @details <tr><td>Kentucky Speedway</td><td>11600</td><td>38.7125430</td><td>-84.9184690</td></tr>
 * @details <tr><td>Kia Proving Grounds</td><td>11700</td><td>35.0486190</td><td>-118.0326250</td></tr>
 * @details <tr><td>Knockhill</td><td>11800</td><td>56.1308984</td><td>-3.5065673</td></tr>
 * @details <tr><td>Kyalami</td><td>11900</td><td>-25.9987750</td><td>28.0698990</td></tr>
 * @details <tr><td>Laguna Seca</td><td>12000</td><td>36.5864530</td><td>-121.7566080</td></tr>
 * @details <tr><td>Lakeside</td><td>12100</td><td>-27.2284720</td><td>152.9649060</td></tr>
 * @details <tr><td>La Plata</td><td>12200</td><td>-34.9795260</td><td>-58.1818520</td></tr>
 * @details <tr><td>Las Flores</td><td>12300</td><td>-36.0065460</td><td>-59.0711390</td></tr>
 * @details <tr><td>Las Vegas MS Inner</td><td>12400</td><td>36.2722840</td><td>-115.0097380</td></tr>
 * @details <tr><td>Las Vegas MS Oval</td><td>12500</td><td>36.2745020</td><td>-115.0126120</td></tr>
 * @details <tr><td>Las Vegas MS Road</td><td>12600</td><td>36.2681170</td><td>-115.0168450</td></tr>
 * @details <tr><td>Lausitzring</td><td>12700</td><td>51.5349480</td><td>13.9275260</td></tr>
 * @details <tr><td>Le Mans</td><td>12800</td><td>47.9515270</td><td>0.2075357</td></tr>
 * @details <tr><td>Lime Rock</td><td>12900</td><td>41.9286420</td><td>-73.3809750</td></tr>
 * @details <tr><td>Long Beach</td><td>13000</td><td>33.7622420</td><td>-118.1871890</td></tr>
 * @details <tr><td>Lowes</td><td>13100</td><td>35.3522640</td><td>-80.6855880</td></tr>
 * @details <tr><td>Lurcy-Levis</td><td>13200</td><td>46.7171991</td><td>2.9525055</td></tr>
 * @details <tr><td>Macau</td><td>13300</td><td>22.1986550</td><td>113.5585940</td></tr>
 * @details <tr><td>Magny-Cours Club</td><td>13400</td><td>46.8670652</td><td>3.1571734</td></tr>
 * @details <tr><td>Magny-Cours F1</td><td>13500</td><td>46.8631896</td><td>3.1621991</td></tr>
 * @details <tr><td>Mallala</td><td>13600</td><td>-34.4152070</td><td>138.5058660</td></tr>
 * @details <tr><td>Manfeild</td><td>13700</td><td>-40.2357910</td><td>175.5584390</td></tr>
 * @details <tr><td>Mantorp Park</td><td>13800</td><td>58.3691120</td><td>15.2837690</td></tr>
 * @details <tr><td>Manzanita</td><td>13900</td><td>33.4046650</td><td>-112.1323620</td></tr>
 * @details <tr><td>Mar de Ajo</td><td>14000</td><td>-36.7105660</td><td>-56.7204140</td></tr>
 * @details <tr><td>Mar del Plata</td><td>14100</td><td>-37.9947710</td><td>-57.6387280</td></tr>
 * @details <tr><td>Martinsville</td><td>14200</td><td>36.6342320</td><td>-79.8522730</td></tr>
 * @details <tr><td>Marysville</td><td>14300</td><td>39.1371760</td><td>-121.5579430</td></tr>
 * @details <tr><td>Megara</td><td>14400</td><td>37.9870210</td><td>23.3629060</td></tr>
 * @details <tr><td>Memphis Motorsports</td><td>14500</td><td>35.2821790</td><td>-89.9468410</td></tr>
 * @details <tr><td>Michigan Intl</td><td>14600</td><td>42.0676420</td><td>-84.2447410</td></tr>
 * @details <tr><td>Mid America</td><td>14700</td><td>41.0245200</td><td>-95.8213590</td></tr>
 * @details <tr><td>Mid-Ohio</td><td>14800</td><td>40.6894999</td><td>-82.6352440</td></tr>
 * @details <tr><td>Miller</td><td>15100</td><td>40.5831779</td><td>-112.3763750</td></tr>
 * @details <tr><td>Miller East</td><td>14900</td><td>40.5831510</td><td>-112.3763930</td></tr>
 * @details <tr><td>Miller Full</td><td>15000</td><td>40.5831470</td><td>-112.3763750</td></tr>
 * @details <tr><td>Miller West</td><td>15200</td><td>40.5830940</td><td>-112.3824330</td></tr>
 * @details <tr><td>Milwakee</td><td>15300</td><td>43.0204290</td><td>-88.0129040</td></tr>
 * @details <tr><td>Misano</td><td>15400</td><td>43.9618419</td><td>12.6840103</td></tr>
 * @details <tr><td>Monaco</td><td>15500</td><td>43.7350250</td><td>7.4212380</td></tr>
 * @details <tr><td>Mondello Park</td><td>15600</td><td>53.2574300</td><td>-6.7445430</td></tr>
 * @details <tr><td>Monticello</td><td>15700</td><td>41.6198340</td><td>-74.6974879</td></tr>
 * @details <tr><td>Monza</td><td>15800</td><td>45.6177419</td><td>9.2809437</td></tr>
 * @details <tr><td>Morgan Park</td><td>15900</td><td>-28.2620460</td><td>152.0363919</td></tr>
 * @details <tr><td>Moroso</td><td>16000</td><td>26.9207020</td><td>-80.3058260</td></tr>
 * @details <tr><td>Mosport</td><td>16100</td><td>44.0543970</td><td>-78.6744669</td></tr>
 * @details <tr><td>Most</td><td>16200</td><td>50.5194370</td><td>13.6077450</td></tr>
 * @details <tr><td>MSR Cresson</td><td>16300</td><td>32.5231270</td><td>-97.6152580</td></tr>
 * @details <tr><td>MSR Houston</td><td>16400</td><td>29.2790530</td><td>-95.4223989</td></tr>
 * @details <tr><td>Mugello</td><td>16500</td><td>43.9975940</td><td>11.3715280</td></tr>
 * @details <tr><td>Myrtle Beach</td><td>16600</td><td>33.7459490</td><td>-78.9525710</td></tr>
 * @details <tr><td>NakornChaisri</td><td>16700</td><td>13.9108890</td><td>100.1676640</td></tr>
 * @details <tr><td>Nashville Motorsports Speedway</td><td>16800</td><td>36.1308390</td><td>-86.7630000</td></tr>
 * @details <tr><td>Nashville Super Speedway</td><td>16900</td><td>36.0462430</td><td>-86.4096809</td></tr>
 * @details <tr><td>Nazereth</td><td>17000</td><td>40.7274030</td><td>-75.3188830</td></tr>
 * @details <tr><td>Nelson Ledges</td><td>17100</td><td>41.3070950</td><td>-81.0141140</td></tr>
 * @details <tr><td>New Hampshire Motorspeedway</td><td>17200</td><td>43.3630780</td><td>-71.4620140</td></tr>
 * @details <tr><td>New Jersey Lighting</td><td>17300</td><td>39.3615330</td><td>-75.0539520</td></tr>
 * @details <tr><td>New Jersey Thunderbolt</td><td>17400</td><td>39.3605150</td><td>-75.0704170</td></tr>
 * @details <tr><td>NOLA North Track</td><td>17500</td><td>29.8854166</td><td>-90.1991500</td></tr>
 * @details <tr><td>No Problem</td><td>17600</td><td>30.0183490</td><td>-91.0807680</td></tr>
 * @details <tr><td>North Florida Park</td><td>17700</td><td>30.5748900</td><td>-83.1564110</td></tr>
 * @details <tr><td>Nueve de Julio</td><td>17800</td><td>-35.4348950</td><td>-60.9112370</td></tr>
 * @details <tr><td>Nurburgring</td><td>17900</td><td>50.3355833</td><td>6.9475333</td></tr>
 * @details <tr><td>Ocala GP</td><td>18000</td><td>29.2280470</td><td>-82.1901150</td></tr>
 * @details <tr><td>Okayama</td><td>18100</td><td>34.9142940</td><td>134.2189420</td></tr>
 * @details <tr><td>Oporto</td><td>18200</td><td>41.1735190</td><td>-8.6851820</td></tr>
 * @details <tr><td>OReilly</td><td>18300</td><td>39.8125130</td><td>-86.3418360</td></tr>
 * @details <tr><td>Oschersleben</td><td>18400</td><td>52.0275380</td><td>11.2781340</td></tr>
 * @details <tr><td>Oulton Park</td><td>18500</td><td>53.1800337</td><td>-2.6128610</td></tr>
 * @details <tr><td>Pacific</td><td>18600</td><td>47.3206610</td><td>-122.1437440</td></tr>
 * @details <tr><td>Paul Ricard</td><td>18700</td><td>43.2511709</td><td>5.7930340</td></tr>
 * @details <tr><td>Pembrey</td><td>18800</td><td>51.7058670</td><td>-4.3238440</td></tr>
 * @details <tr><td>Phillip Island</td><td>18900</td><td>-38.5013350</td><td>145.2315488</td></tr>
 * @details <tr><td>Phoenix Intl</td><td>19000</td><td>33.3759980</td><td>-112.3114180</td></tr>
 * @details <tr><td>Pikes Peak</td><td>19200</td><td>38.5909460</td><td>-104.6782120</td></tr>
 * @details <tr><td>Pikes Peak Hill Climb</td><td>19100</td><td>38.8226000</td><td>-105.0089000</td></tr>
 * @details <tr><td>Pocono</td><td>19300</td><td>41.0526250</td><td>-75.5117690</td></tr>
 * @details <tr><td>Portimao</td><td>19400</td><td>37.2297999</td><td>-8.6299166</td></tr>
 * @details <tr><td>Portland</td><td>19600</td><td>45.5949830</td><td>-122.6945170</td></tr>
 * @details <tr><td>Portland Intl</td><td>19500</td><td>45.5940750</td><td>-122.6909140</td></tr>
 * @details <tr><td>Prince George</td><td>19700</td><td>-33.0495300</td><td>27.8698790</td></tr>
 * @details <tr><td>Pukekohe</td><td>19800</td><td>-37.2178190</td><td>174.9166770</td></tr>
 * @details <tr><td>Putnam</td><td>19900</td><td>39.5823040</td><td>-86.7423200</td></tr>
 * @details <tr><td>Qatar</td><td>20000</td><td>25.4891830</td><td>51.4495490</td></tr>
 * @details <tr><td>Queensland Raceway</td><td>20100</td><td>-27.6906460</td><td>152.6546360</td></tr>
 * @details <tr><td>Reno Fernley Raceway</td><td>20200</td><td>39.5394040</td><td>-119.2417810</td></tr>
 * @details <tr><td>Richmond Intl</td><td>20300</td><td>37.5910960</td><td>-77.4196610</td></tr>
 * @details <tr><td>Rijeka</td><td>20400</td><td>45.3827519</td><td>14.5092920</td></tr>
 * @details <tr><td>Road America</td><td>20600</td><td>43.7980170</td><td>-87.9896190</td></tr>
 * @details <tr><td>Road America Short</td><td>20500</td><td>43.8031010</td><td>-87.9924790</td></tr>
 * @details <tr><td>Road Atlanta</td><td>20700</td><td>34.1503860</td><td>-83.8142110</td></tr>
 * @details <tr><td>Rockingham</td><td>20800</td><td>34.9758610</td><td>-79.6108979</td></tr>
 * @details <tr><td>Roebling Road</td><td>20900</td><td>32.1670440</td><td>-81.3228270</td></tr>
 * @details <tr><td>Sachsenring</td><td>21000</td><td>50.7917130</td><td>12.6882590</td></tr>
 * @details <tr><td>Salzburgring</td><td>21100</td><td>47.8230730</td><td>13.1690450</td></tr>
 * @details <tr><td>Sandia</td><td>21200</td><td>35.0205890</td><td>-106.8588520</td></tr>
 * @details <tr><td>Sandown</td><td>21300</td><td>-37.9490784</td><td>145.1643209</td></tr>
 * @details <tr><td>Sebring</td><td>21600</td><td>27.4502500</td><td>-81.3537360</td></tr>
 * @details <tr><td>Sebring Short 1</td><td>21400</td><td>27.4569020</td><td>-81.3496510</td></tr>
 * @details <tr><td>Sebring Short 2</td><td>21500</td><td>27.4561170</td><td>-81.3539690</td></tr>
 * @details <tr><td>Second Creek</td><td>21700</td><td>39.8603470</td><td>-104.7895990</td></tr>
 * @details <tr><td>Sendai</td><td>21800</td><td>38.2860940</td><td>140.6218910</td></tr>
 * @details <tr><td>Sentul</td><td>21900</td><td>-6.5364540</td><td>106.8563530</td></tr>
 * @details <tr><td>Sepang</td><td>22000</td><td>2.7607436</td><td>101.7380675</td></tr>
 * @details <tr><td>Shannonville</td><td>22100</td><td>44.2252280</td><td>-77.1598040</td></tr>
 * @details <tr><td>Silverstone Arena</td><td>22200</td><td>52.0787198</td><td>-1.0174020</td></tr>
 * @details <tr><td>Snetterton</td><td>22300</td><td>52.4634064</td><td>0.9446992</td></tr>
 * @details <tr><td>Spa</td><td>22400</td><td>50.4431666</td><td>5.9661833</td></tr>
 * @details <tr><td>Speed World Oval</td><td>22500</td><td>28.3982630</td><td>-81.5785960</td></tr>
 * @details <tr><td>Spokane</td><td>22700</td><td>47.6627470</td><td>-117.5708780</td></tr>
 * @details <tr><td>Spokane Short</td><td>22600</td><td>47.6627430</td><td>-117.5708450</td></tr>
 * @details <tr><td>Spring Mountain 1 5</td><td>22800</td><td>36.1752100</td><td>-115.9105900</td></tr>
 * @details <tr><td>Spring Mountain 3 4</td><td>22900</td><td>36.1686500</td><td>-115.9100150</td></tr>
 * @details <tr><td>St Petersburg</td><td>23000</td><td>27.7654280</td><td>-82.6296080</td></tr>
 * @details <tr><td>Stratotech</td><td>23100</td><td>53.7363760</td><td>-113.2339460</td></tr>
 * @details <tr><td>Streets of Willow</td><td>23200</td><td>34.8747970</td><td>-118.2587400</td></tr>
 * @details <tr><td>Sugo</td><td>23300</td><td>38.1425139</td><td>140.7746030</td></tr>
 * @details <tr><td>Summit Point</td><td>23600</td><td>39.2351950</td><td>-77.9690690</td></tr>
 * @details <tr><td>Summit Point Jefferson</td><td>23400</td><td>39.2341420</td><td>-77.9723710</td></tr>
 * @details <tr><td>Summit Point Shenandoah</td><td>23500</td><td>39.2412820</td><td>-77.9797450</td></tr>
 * @details <tr><td>Surfers Paradise</td><td>23700</td><td>-27.9861680</td><td>153.4272720</td></tr>
 * @details <tr><td>Suzuka</td><td>23800</td><td>34.8432100</td><td>136.5404439</td></tr>
 * @details <tr><td>Symmons Plains</td><td>23900</td><td>-41.6576961</td><td>147.2500363</td></tr>
 * @details <tr><td>Talladega GP</td><td>24000</td><td>33.5033590</td><td>-85.9996030</td></tr>
 * @details <tr><td>Talladega Oval</td><td>24100</td><td>33.5632630</td><td>-86.0692120</td></tr>
 * @details <tr><td>Taupo</td><td>24200</td><td>-38.6626850</td><td>176.1469370</td></tr>
 * @details <tr><td>Teretonga</td><td>24300</td><td>-46.4409270</td><td>168.2630720</td></tr>
 * @details <tr><td>Texas Motor Speedway</td><td>24400</td><td>33.3729000</td><td>-97.2842380</td></tr>
 * @details <tr><td>Texas World Speedway</td><td>24500</td><td>30.5380070</td><td>-96.2244270</td></tr>
 * @details <tr><td>The Glen</td><td>24600</td><td>42.3409620</td><td>-76.9289170</td></tr>
 * @details <tr><td>Thompson Speedway</td><td>24700</td><td>41.9817570</td><td>-71.8255129</td></tr>
 * @details <tr><td>Thruxton</td><td>24800</td><td>51.2078060</td><td>-1.6091975</td></tr>
 * @details <tr><td>ThunderHill</td><td>24900</td><td>39.5384670</td><td>-122.3311560</td></tr>
 * @details <tr><td>Tokachi</td><td>25000</td><td>42.6306340</td><td>143.2922850</td></tr>
 * @details <tr><td>Toronto Motorsports Park</td><td>25100</td><td>42.9028630</td><td>-79.8579990</td></tr>
 * @details <tr><td>Townsville</td><td>25200</td><td>-19.2720600</td><td>146.8109188</td></tr>
 * @details <tr><td>Tsukuba</td><td>25300</td><td>36.1500820</td><td>139.9193620</td></tr>
 * @details <tr><td>Twin Ring Montegi</td><td>25400</td><td>36.5330320</td><td>140.2267130</td></tr>
 * @details <tr><td>Val de Vienne</td><td>25500</td><td>46.1972590</td><td>0.6356030</td></tr>
 * @details <tr><td>Valencia</td><td>25600</td><td>39.4840463</td><td>0.6300597</td></tr>
 * @details <tr><td>Vallelunga</td><td>25700</td><td>42.1577089</td><td>12.3689960</td></tr>
 * @details <tr><td>Varano</td><td>25800</td><td>44.6806980</td><td>10.0209050</td></tr>
 * @details <tr><td>VIR</td><td>26100</td><td>36.5686420</td><td>-79.2077890</td></tr>
 * @details <tr><td>Virginia Intl Patriot</td><td>25900</td><td>36.5604350</td><td>-79.2062360</td></tr>
 * @details <tr><td>Virginia Intl South</td><td>26000</td><td>36.5339910</td><td>-79.2066550</td></tr>
 * @details <tr><td>Volvo Proving Grounds</td><td>26200</td><td>33.6969470</td><td>-112.5043590</td></tr>
 * @details <tr><td>Wakefield</td><td>26300</td><td>-34.8401540</td><td>149.6851580</td></tr>
 * @details <tr><td>Warwick Farm</td><td>26400</td><td>-33.9111700</td><td>150.9451960</td></tr>
 * @details <tr><td>Waterford Hills</td><td>26500</td><td>42.7085760</td><td>-83.3912500</td></tr>
 * @details <tr><td>Watkins Glen</td><td>26600</td><td>42.3410310</td><td>-76.9288750</td></tr>
 * @details <tr><td>Welkom</td><td>26700</td><td>-27.9047140</td><td>26.7110550</td></tr>
 * @details <tr><td>West Palm Beach</td><td>26800</td><td>26.9206970</td><td>-80.3057890</td></tr>
 * @details <tr><td>Willow Springs</td><td>26900</td><td>34.8715530</td><td>-118.2636560</td></tr>
 * @details <tr><td>Winton</td><td>27000</td><td>-36.5188820</td><td>146.0871151</td></tr>
 * @details <tr><td>Zandvoort</td><td>27100</td><td>52.3888510</td><td>4.5407599</td></tr>
 * @details <tr><td>Zhuhai</td><td>27200</td><td>22.3668940</td><td>113.5600980</td></tr>
 * @details <tr><td>Zolder</td><td>27300</td><td>50.9890300</td><td>5.2557240</td></tr>
 * @details <tr><td>Zwartkops</td><td>27400</td><td>-25.8100210</td><td>28.1124940</td></tr>
 * @details </table>
 *
 * @param radius detection radius (metres) in the range [1, 1000]
 * @param lat1 latitude of custom beacon point 1 in the range [-850000000, 850000000]
 * @param lon1 longitude of custom beacon point 1 in the range [-1800000000, 1800000000]
 * @param bn1 beacon number for custom beacon 1 in the range [1, 2147483647]
 * @param lat2 latitude of custom beacon point 2 in the range [-850000000, 850000000]
 * @param lon2 longitude of custom beacon point 2 in the range [-1800000000, 1800000000]
 * @param bn2 beacon number for custom beacon 2 in the range [1, 2147483647]
 * @param lat3 latitude of custom beacon point 3 in the range [-850000000, 850000000]
 * @param lon3 longitude of custom beacon point 3 in the range [-1800000000, 1800000000]
 * @param bn3 beacon number for custom beacon 3 in the range [1, 2147483647]
 * @param lat4 latitude of custom beacon point 4 in the range [-850000000, 850000000]
 * @param lon4 longitude of custom beacon point 4 in the range [-1800000000, 1800000000]
 * @param bn4 beacon number for custom beacon 4 in the range [1, 2147483647]
 * @return true for success, false if an invalid beacon point or detection radius is specified.
 */

__warn_unused_result bool gpslap_init(
    f32 radius,
    s32e7 lat1, s32e7 lon1, s32 bn1,
    s32e7 lat2, s32e7 lon2, s32 bn2,
    s32e7 lat3, s32e7 lon3, s32 bn3,
    s32e7 lat4, s32e7 lon4, s32 bn4);

/**
 * @fn s32 gpslap_calculate(bool valid, s32e7 lat, s32e7 lon, u32 ticks)
 * @arg ScriptName Calculate
 *
 * @brief Calculate GPS lap beacon.
 *
 * @details <p>Processes the provided GPS coordinates against the list of beacon
 * @details locations.</p>
 * @details <p>See GPS.Init for a list of supported beacon locations.</p>
 * @details <p>This function must be supplied GPS position updates at a minimum of
 * @details 1Hz.</p>
 * @details <p>When a GPS lap is detected the value returned by the
 * @details GPSLap.BeaconTicks() function will change to reflect the time at which
 * @details the beacon was detected.</p>
 * @details <p>The return value will be one of the following:</p>
 * @details <table class=param>
 * @details <tr><th>Return Value</th><th>Meaning</th></tr>
 * @details <tr><td>0</td><td>OK</td></tr>
 * @details <tr><td>1</td><td>No new GPS data provided</td></tr>
 * @details <tr><td>2</td><td>Longitude out of range</td></tr>
 * @details <tr><td>3</td><td>Latitude out of range</td></tr>
 * @details <tr><td>4</td><td>No beacon within 1km</td></tr>
 * @details <tr><td>5</td><td>GPS update rate too slow</td></tr>
 * @details <tr><td>6</td><td>Moved more than 10km in last update</td></tr>
 * @details <tr><td>7</td><td>Moved less than 1cm in last update</td></tr>
 * @details <tr><td>8</td><td>No intersection detected</td></tr>
 * @details <tr><td>9</td><td>Intersection outside detection radius</td></tr>
 * @details <tr><td>10</td><td>Detected beacon</td></tr>
 * @details </table>
 *
 * @param valid gps location is valid
 * @param lat current latitude
 * @param lon current longitude
 * @param ticks system ticks at time of measurement
 * @return diagnostic information about GPS lap calculation
 */

s32 gpslap_calculate(bool valid, s32e7 lat, s32e7 lon, u32 ticks);

/**
 * @fn s32 gpslap_beacon_number()
 * @arg ScriptName BeaconNumber
 *
 * @brief Get closest beacon number.
 *
 * @details <p>Returns the number of the closest beacon.</p>
 * @details <p>If there is no beacon within a radius of 1km returns 0.</p>
 *
 * @return number of closest beacon
 */

static __inline __warn_unused_result s32 gpslap_beacon_number(void)
{
	return gpslap_number;
}

/**
 * @fn u32 gpslap_beacon_ticks()
 * @arg ScriptName BeaconTicks
 *
 * @brief Get tick count of last beacon crossing.
 *
 * @return tick count of last beacon crossing
 */

static __inline __warn_unused_result u32 gpslap_beacon_ticks(void)
{
	return gpslap_ticks;
}

#endif // __ECU_GPSLAP_H__

