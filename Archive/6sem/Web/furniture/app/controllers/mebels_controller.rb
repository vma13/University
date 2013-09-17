class MebelsController < ApplicationController
  # GET /mebels
  # GET /mebels.xml
  def index
    @mebels = Mebel.all

    respond_to do |format|
      format.html # index.html.erb
      format.xml  { render :xml => @mebels }
    end
  end

  # GET /mebels/1
  # GET /mebels/1.xml
  def show
    @mebel = Mebel.find(params[:id])

    respond_to do |format|
      format.html # show.html.erb
      format.xml  { render :xml => @mebel }
    end
  end

  # GET /mebels/new
  # GET /mebels/new.xml
  def new
    @mebel = Mebel.new

    respond_to do |format|
      format.html # new.html.erb
      format.xml  { render :xml => @mebel }
    end
  end

  # GET /mebels/1/edit
  def edit
    @mebel = Mebel.find(params[:id])
  end

  # POST /mebels
  # POST /mebels.xml
  def create
    @mebel = Mebel.new(params[:mebel])

    respond_to do |format|
      if @mebel.save
        format.html { redirect_to(@mebel, :notice => 'Mebel was successfully created.') }
        format.xml  { render :xml => @mebel, :status => :created, :location => @mebel }
      else
        format.html { render :action => "new" }
        format.xml  { render :xml => @mebel.errors, :status => :unprocessable_entity }
      end
    end
  end

  # PUT /mebels/1
  # PUT /mebels/1.xml
  def update
    @mebel = Mebel.find(params[:id])

    respond_to do |format|
      if @mebel.update_attributes(params[:mebel])
        format.html { redirect_to(@mebel, :notice => 'Mebel was successfully updated.') }
        format.xml  { head :ok }
      else
        format.html { render :action => "edit" }
        format.xml  { render :xml => @mebel.errors, :status => :unprocessable_entity }
      end
    end
  end

  # DELETE /mebels/1
  # DELETE /mebels/1.xml
  def destroy
    @mebel = Mebel.find(params[:id])
    @mebel.destroy

    respond_to do |format|
      format.html { redirect_to(mebels_url) }
      format.xml  { head :ok }
    end
  end
end
